#include <stdlib.h>
#include "src/log.h"

FILE* logfp = (FILE*)NULL;
static FILE* local_log_fp = (FILE*)NULL;
loglvl_t loglvl = LOG_LVL_INFO;

FILE*
init_log(char* log_filepath, loglvl_t log_level)
{
  if (log_filepath == (char*)NULL)
    {
      fprintf(stderr, "Error: cannot initialize logging without a file pathname\n");
      return (FILE*)NULL;
    }

  local_log_fp = fopen(log_filepath, "w");
  if (local_log_fp == (FILE*)NULL)
    {
      const char* logfmt = "cannot open logging file '%s'";
      char logmsg[MAX_LOG_MSG_LENGTH];
      snprintf(logmsg, MAX_LOG_MSG_LENGTH, logfmt, log_filepath);
      perror(logmsg);
    }

  return local_log_fp;
}

int
do_log(FILE* logfp, loglvl_t loglvl, char* logfmt, ...)
{
  unsigned int n_printed_args = 0;
  va_list ap;
  char* my_logfmt = strndup(logfmt, strnlen(logfmt, MAX_LOGFMT_LENGTH));
  char* logptr = strtok(my_logfmt, "%");

  if (logptr)
    {
      while(logptr = strtok((char*)NULL, "! \"'|()[],:;\n\t"))
        {
          switch (logptr[strlen(logptr)-1])
            {
            case 'd':
              {
                int is_long = 0;
                if (strlen(logptr) > 1)
                  if (logptr[0] == 'l')
                    is_long = 1;
                n_printed_args++;
              }
              break;
            case 'u':
              {
                int is_long = 0;
                if (strlen(logptr) > 1)
                  if (logptr[0] == 'l')
                    is_long = 1;
                n_printed_args++;
              }
              break;
            case 'f': 
            case 'F':
              n_printed_args++;
              break;
            case 'g': 
            case 'G':
              n_printed_args++;
              break;
            case 's':
              {
                int len = -1;
                if (strlen(logptr) > 1)
                  {
                    len = atoi(logptr);
                  }
                n_printed_args++;
              }
              break;
            case 'p':
              n_printed_args++;
              break;
            default:
              fprintf(stdout, "\n Option inconnue, veuillez entrer une option valide\n");
              break;
            }
        }
    }
  va_start(ap, logfmt);
  vfprintf(logfp, my_logfmt, ap);
  return(n_printed_args);
}

void
end_log(FILE* log_fp)
{

  if (log_fp == (FILE*)NULL || log_fp == local_log_fp)
    {
      log_fp = local_log_fp;
      local_log_fp = (FILE*)NULL;
    }
  if (log_fp != (FILE*)NULL)
    {
      fclose(log_fp);
      log_fp = (FILE*)NULL;
    }
}
