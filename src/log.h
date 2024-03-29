#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
extern int errno;
extern int sys_nerr;
extern const char * const sys_errlist[];
#define MAX_LOGFMT_LENGTH  4096
#define MAX_LOG_MSG_LENGTH 1024
#ifdef     DO_LOG
#define LOG(log_lvl, logfmt, ...)	{if (loglvl >= log_lvl) do_log(logfp, loglvl, logfmt, __VA_ARGS__);}
#else
#define LOG(log_lvl, logfmt, ...)
#endif

enum loglvl_e {
  LOG_LVL_NONE = 0,
  LOG_LVL_INFO,
  LOG_LVL_WARN,
  LOG_LVL_ERR,
  LOG_LVL_DBG
};
typedef enum loglvl_e loglvl_t;

extern FILE* logfp;

extern loglvl_t loglvl;

FILE* init_log(char* , loglvl_t );
int do_log(FILE* , loglvl_t , char* , ... );
void end_log(FILE*);
