#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <stdbool.h>
#include "src/log.h"
#include "list/list.h"
#define ERR_MESSAGE_MAX_SIZE    1024
char** global_envp = (char**)NULL;
int main(int, char**, char**);
static struct option long_options[] =
  {
    {"help",          no_argument,       0,  'h' },
    {"verbose",       no_argument,       0,  'v' },
    {"display",       no_argument,       0,  'd' },
    {"init",          no_argument,       0,  'i' },
    {"load",          required_argument, 0,  'l' },
    {"save",          required_argument, 0,  's' },
    {"test",          required_argument, 0,  't' },
    {"append",        required_argument, 0,  'A' },
    {"prepend",       required_argument, 0,  'P' },
    {"insert",        no_argument,       0,  'I' },
    {"delhead",       no_argument,       0,  'x' },
    {"deltail",       no_argument,       0,  'X' },
    {"remove",        required_argument, 0,  'r' },
    {"quit",          no_argument,       0,  'q' },
    {"interactive",   no_argument,       0,  'N' },
    {0,               0,                 0,  0 }
  };
    
listechainee_ptr curlist = NULL;

extern char* optarg;
static int one_opt = 0;
static int v_opt = 0;
static int h_opt = 0;
static int d_opt = 0;
static int l_opt = 0;
static int s_opt = 0;
static int i_opt = 0;
static int t_opt = 0;
static int A_opt = 0;
static int P_opt = 0;
static int I_opt = 0;
static int x_opt = 0;
static int X_opt = 0;
static int r_opt = 0;
static int q_opt = 0;
static int N_opt = 0;


char *progname = (char *)NULL;
char *blankname = (char *)NULL;
char* arg_filename = (char *)NULL;
int arg_elem = 0;
int arg_index = -1;


void
print_help(void)
{
    fprintf(stdout, "%s: Help menu: %s                                                                                      \n", progname, progname);
    fprintf(stdout, "%s         Options:                                                                                    \n", blankname, blankname);
    fprintf(stdout, "%s            -h : Display help menu                                                                   \n", blankname, blankname);
    fprintf(stdout, "%s            -v : Increase verbosity                                                                  \n", blankname, blankname);
    fprintf(stdout, "%s            -d : Display the current list                                                            \n", blankname, blankname);
    fprintf(stdout, "%s            -i : Initialize the list                                                                 \n", blankname, blankname);
    fprintf(stdout, "%s            -l <filename> : Load a list from a file                                                  \n", blankname, blankname);
    fprintf(stdout, "%s            -s <filename> : Save the current list to a file                                          \n", blankname, blankname);
    fprintf(stdout, "%s            -t <element> : Test if an element is in the list                                         \n", blankname, blankname);
    fprintf(stdout, "%s            -A <element> : Append an element to the list                                             \n", blankname, blankname);
    fprintf(stdout, "%s            -P <element> : Prepend an element to the list                                            \n", blankname, blankname);
    fprintf(stdout, "%s            -I : Insert an element at the specified index                                            \n", blankname, blankname);
    fprintf(stdout, "%s            -x : Delete the head of the list                                                         \n", blankname, blankname);
    fprintf(stdout, "%s            -X : Delete the end of the list                                                          \n", blankname, blankname);
    fprintf(stdout, "%s            -r <element> : Remove an element from the list                                           \n", blankname, blankname);
    fprintf(stdout, "%s            -N : Enter interactive mode                                                              \n", blankname, blankname);

}


/*----------------------------Debut menu interactif (je n'ai pas réussi a le faire moi meme donc j'ai pris celui du prof (rcoscali sur github)---------------------*/
void
print_help_menu(void)
{
  fprintf(stdout, "\nHelp for interactive menu:                                                                             \n");
  fprintf(stdout, "-------------------------                                                                                \n");
  fprintf(stdout, "Enter the letter for selecting a command. Accepted commands are:                                         \n");
  fprintf(stdout, "'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'H', 'i', 'j', 'k', 'm', 'q'                                     \n");
  fprintf(stdout, "     'a':   Display current list                                                                         \n");
  fprintf(stdout, "     'b':   Reset/Init current list                                                                      \n");
  fprintf(stdout, "     'c':   Load current list from file                                                                  \n");
  fprintf(stdout, "     'd':   Save current list to file                                                                    \n");
  fprintf(stdout, "     'e':   Test if an element is in current list                                                        \n");
  fprintf(stdout, "     'f':   Append an element to current list                                                            \n");
  fprintf(stdout, "     'g':   Prepend an element to current list                                                           \n");
  fprintf(stdout, "     'h':   Insert element after an element in current list                                              \n");
  fprintf(stdout, "     'H':   Insert element after index in current list                                                   \n");
  fprintf(stdout, "     'i':   Delete at end of current list                                                                \n");
  fprintf(stdout, "     'j':   Delete at start of current list                                                              \n");
  fprintf(stdout, "     'k':   Remove element from current list                                                             \n");
  fprintf(stdout, "     'm':   Display help for the menu                                                                    \n");
  fprintf(stdout, "     'q':   Exit the menu                                                                                \n");
  fprintf(stdout, "Select an entry by its letter ?                                                                          ");
}




listechainee_ptr
enter_interactive_mode(listechainee_ptr list)
{
  char entry = 0;
  int element;
  int elementat;
  int index;
  char filename[50];
  int menu = 1;
  
  while(menu)
    {
      fprintf(stdout, "\nMenu:\n");
      fprintf(stdout, "----:\n");
      fprintf(stdout, "     a) Display current list\n");
      fprintf(stdout, "     b) Reset/Init current list\n");
      fprintf(stdout, "     c) Load current list from file\n");
      fprintf(stdout, "     d) Save current list to file\n");
      fprintf(stdout, "     e) Test if an element is in current list\n");
      fprintf(stdout, "     f) Append an element to current list\n");
      fprintf(stdout, "     g) Prepend an element to current list\n");
      fprintf(stdout, "     h) Insert element after an element in current list\n");
      fprintf(stdout, "     H) Insert element after index in current list\n");
      fprintf(stdout, "     i) Delete at end of current list\n");
      fprintf(stdout, "     j) Delete at start of current list\n");
      fprintf(stdout, "     k) Remove element from current list\n");
      fprintf(stdout, "     m) Display help for the menu\n");
      fprintf(stdout, "     q) Exit the menu\n");
      fprintf(stdout, "Select an entry by its letter ? ");
      fflush(stdin);
      fscanf(stdin, "\n%c", &entry);
      fprintf(stdout, "\n");

      switch (entry)
        {
        case 'a':
          display_list(curlist);
          break;

        case 'b':
          init_list();
          break;

        case 'c':
          fprintf(stdout, "Filename to load ? ");
          fflush(stdin);
          fscanf(stdin, "%s", (char*)&filename);
          curlist = load_list(filename);
          display_list(curlist);
          break;

        case 'd':
          fprintf(stdout, "Filename to save ? ");
          fflush(stdin);
          fscanf(stdin, "%s", (char*)&filename);
          curlist = save_list(curlist, filename);
          break;

        case 'e':
          fprintf(stdout, "Element to find ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &element);
          fprintf(stdout, "List contains element '%d' : %s\n", element, test_elem_in_list(curlist, element) ? "yes" : "no");
          break;

        case 'f':
          fprintf(stdout, "Element to append ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &element);
          curlist = append_list(curlist, element);
          display_list(curlist);
          break;

        case 'g':
          fprintf(stdout, "Element to prepend ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &element);
          curlist = prepend_list(curlist, element);
          display_list(curlist);
          break;

        case 'h':
          {
            fprintf(stdout, "Element to insert ? ");
            fflush(stdin);
            fscanf(stdin, "%d", &element);
            fprintf(stdout, "Insert after element ? ");
            fflush(stdin);
            fscanf(stdin, "%d", &elementat);
            int atindex = find_elem_ix(curlist, elementat);
            curlist = insert_elem_in_list(curlist, atindex, element);
          }
          break;

        case 'H':
          fprintf(stdout, "Element to insert ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &element);
          fprintf(stdout, "Insert after index ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &index);
          curlist = insert_elem_in_list(curlist, index, element);            
          break;

        case 'i':
          curlist = delete_end_of_list(curlist);
          display_list(curlist);
          break;

        case 'j':
          curlist = delete_start_of_list(curlist);
          display_list(curlist);
          break;

        case 'k':
          fprintf(stdout, "Element to delete ? ");
          fflush(stdin);
          fscanf(stdin, "%d", &element);
          curlist = delete_elem_in_list(curlist, element);
          display_list(curlist);
          break;

        case 'q':
          menu = 0;
          break;

        case 'm':
          print_help_menu();
          break;

        default:
          fprintf(stdout, "\n!! Option inconnue, veuillez entrer une option valable parmis les commandes:\n");
          print_help_menu();
        }
    }
  return curlist;
}

/*-------------------------------------------------Fin menu interactive---------------------------------------------------------*/




int
main(int argc, char** argv, char** envp)
{
  int c;
  int digit_optind = 0;
  global_envp = envp;
  progname = (progname = rindex(argv[0], '/')) ? progname+1 : argv[0];
  blankname = strndup(progname, strlen(progname));
  blankname = memset(blankname, (int)' ', strlen(progname));
  time_t current_time = time((time_t*)NULL);
  char* datestr = ctime(&current_time);
  datestr[strlen(datestr)-1] = '\0';
  char* date_tmp = datestr;

  while(*date_tmp)
    {
      if (*date_tmp == ' ')
        *date_tmp = '_';
      date_tmp++;
    }
  char logfilepath[1024];
  snprintf(logfilepath, 1024, "%s_%s.log", progname, datestr);
  loglvl = LOG_LVL_INFO;
#ifdef DO_LOG
  logfp = init_log(logfilepath, loglvl);
#endif
  init_list();
  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    if ((c = getopt_long(argc, argv,"hvdl:s:it:A:P:IxXr:qN", long_options, &option_index)) == -1)
      break;
    switch (c)
      {
        case 'h':
          h_opt = 1;
          if (v_opt)
            fprintf(stdout, "%s: Info: Un utilisateur a affiché le menu help (-h) !\n", progname);
          LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a affiché le menu help (-h) !\n", progname);
          print_help();
          return 0;
          break;

        case 'v':
          v_opt++;
          if (v_opt)
            fprintf(stdout, "%s: Info: Un utilisateur a augmenté la verbosité (-v) !\n", progname);
          LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a augmenté la verbosité (-v) !\n", progname);
          break;

        case 'd':
          d_opt = 1;
          if (v_opt)
            fprintf(stdout, "%s: Info: Un utilisateur a affiché une liste (-d) !\n", progname);
          LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a affiché une liste (-d) !\n", progname);
          curlist = load_list("list_file.txt");
          display_list(curlist);
          d_opt = 0;
          save_list(curlist, "list_file.txt");
          return 0;
          break;

          case 'i':
            i_opt = 1;
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a initialisé une liste (-i) !\n", progname);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a initialisé une liste (-i) !\n", progname);
            init_list();
            fprintf(stdout, "%s: info: Votre liste a bien été initialisée!\n", progname);
            save_list(curlist, "list_file.txt");
            break;

          case 'l':
            l_opt = 1;
            arg_filename = optarg;
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a chargé une liste depuis un fichier externe (-l) ! :'%s'\n", progname, arg_filename);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a chargé une liste depuis un fichier externe (-l) ! :'%s'\n", progname, arg_filename);
            curlist = load_list(arg_filename);
            fprintf(stdout, "%s: Info: Liste chargée à partir du fichier '%s' !\n", progname, arg_filename);
            save_list(curlist, "list_file.txt");
            display_list(curlist);
            return 0;
            break;

          case 's':
            s_opt = 1;
            arg_filename = optarg;
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a sauvegardé une liste vers un fichier externe (-s) ! :'%s'\n", progname, arg_filename);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a sauvegardé une liste vers un fichier externe (-s) ! :'%s'\n", progname, arg_filename);
            curlist = load_list("list_file.txt");
            save_list(curlist, arg_filename);
            fprintf(stdout, "%s: info: Liste enregistrée dans le fichier '%s' !\n", progname, arg_filename);
            return 0;
            break;

          case 't':
            t_opt = 1;
            arg_elem = atoi(optarg);
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a testé si l'élément '%d' était dans la liste (-l) !\n", progname, arg_elem);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a testé si l'élément '%d' était dans la liste (-l) !\n", progname, arg_elem);
            curlist = load_list("list_file.txt");
            if (test_elem_in_list(curlist, arg_elem)) {
              fprintf(stdout, "%s: Info: L'élement '%d' est dans la liste !\n", progname, arg_elem);
              return 0;
            } else {
              fprintf(stdout, "%s: Info: L'élement '%d' n'est pas dans la liste !\n", progname, arg_elem);
              return 0;
            }
            break;

          case 'A':
            A_opt = 1;
            arg_elem = atoi(optarg);
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a ajouté l'élément '%d' à la fin de la liste (-A) !\n", progname, arg_elem);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a ajouté l'élément '%d' à la fin de la liste (-A) !\n", progname, arg_elem);
            curlist = load_list("list_file.txt");
            curlist = append_list(curlist, arg_elem);
            save_list(curlist, "list_file.txt");
            fprintf(stdout, "%s: Info: Vous avez ajouté l'élément '%d' a la fin de votre liste !\n", progname, arg_elem);
            display_list(curlist);
            break;
            
          case 'P':
            P_opt = 1;
            arg_elem = atoi(optarg);
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a ajouté l'élément '%d' au début de la liste (-P) !\n", progname, arg_elem);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a ajouté l'élément '%d' au début de la liste (-P) !\n", progname, arg_elem);
            curlist = load_list("list_file.txt");
            curlist = prepend_list(curlist, arg_elem);
            save_list(curlist, "list_file.txt");
            fprintf(stdout, "%s: Info: Vous avez ajouté l'élément '%d' au début de votre liste !\n", progname, arg_elem);
            display_list(curlist);
            return 0;
            break;

          case 'I':
            {
              I_opt = 1;
              if (v_opt)
                fprintf(stdout, "%s: Info: Un utilisateur a inséré un élément dans la liste (-I) !\n", progname);
              LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a inséré un élément dans la liste (-I) !\n", progname);
              int index;
              printf("Veuillez entrer l'index ou l'élément doit être inséré. Le premier élément est le 0: ");
              scanf("%d", &index);
              curlist = load_list("list_file.txt");
              int list_length = lenlist(curlist);
              if (index < 0 || index > list_length) {
                printf("Index en dehors de la plage\n");
                break;
              }
              int element;
              printf("Veuillez entrer le chiffre ou le nombre à insérer: ");
              scanf("%d", &element);
              curlist = insert_elem_in_list(curlist, index, element);
              save_list(curlist, "list_file.txt");
              printf("L'élément a été inséré a l'index '%d' avec succès ! \n", index);
              display_list(curlist);
              return 0;
              break;
            }

          case 'x':
            x_opt = 1;
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a supprimé la tête de la liste (-x) !\n", progname);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a supprimé la tête de la liste (-x) !\n", progname);
            curlist = load_list("list_file.txt");
            if (curlist != NULL) {
              curlist = delete_start_of_list(curlist);
              fprintf(stdout, "%s: Info: Tête de liste supprimée !\n", progname);
              save_list(curlist, "list_file.txt");
              display_list(curlist);
              return 0;
            } else {
              fprintf(stdout, "%s: Attention: La liste est vide, nous ne pouvons pas supprimer la tête de la liste !\n", progname);
            }
            break;

          case 'X':
            X_opt = 1;
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a supprimé la fin de la liste (-X) !\n", progname);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a supprimé la fin de la liste (-X) !\n", progname);
            curlist = load_list("list_file.txt");
            if (curlist != NULL) {
              curlist = delete_end_of_list(curlist);
              fprintf(stdout, "%s: Info: Fin de liste supprimée !\n", progname);
              save_list(curlist, "list_file.txt");
              display_list(curlist);
              return 0;
            } else {
              fprintf(stdout, "%s: Attention: La liste est vide, nous ne pouvons pas supprimer la fin de la liste !\n", progname);
            }
            break;

          case 'r':
            r_opt = 1;
            arg_elem = atoi(optarg);
            if (v_opt)
              fprintf(stdout, "%s: Info: Un utilisateur a supprimé l'élément '%d' de la liste (-r) !\n", progname, arg_elem);
            LOG(LOG_LVL_INFO, "%s: Info: Un utilisateur a supprimé l'élément '%d' de la liste (-r) !\n", progname, arg_elem);
            curlist = load_list("list_file.txt");
            if (curlist != NULL) {
              curlist = delete_elem_in_list(curlist, arg_elem);
              if (curlist != NULL) {
                fprintf(stdout, "%s: Info: L'élément '%d' à été supprimé de la liste avec succès !\n", progname, arg_elem);
                save_list(curlist, "list_file.txt");
                display_list(curlist);
                return 0;
              } else {
                  fprintf(stdout, "%s: Attention: L'élément '%d' n'as pas été trouvé dans la liste\n", progname, arg_elem);
                }
            } else {
              fprintf(stdout, "%s: Attention: La liste est vide, nous ne pouvons pas supprimer l'élément de la liste !\n", progname);
            }
            break;
    
          case 'q':
            q_opt = 1;
            if (v_opt)
              fprintf(stdout, "%s: Info: L'option q pour quitter a été utilisé (-q) !\n", progname);
            LOG(LOG_LVL_INFO, "%s: Info: L'option q pour quitter a été utilisé (-q) !\n", progname);
            break;

          case 'N':
            N_opt = 1;
            if (v_opt)
              fprintf(stdout, "%s: Info: L'option N pour entrer dans le menu interactif a été utilisé (-N) ! Accès au menu interactif !\n", progname);
            LOG(LOG_LVL_INFO, "%s: Info: L'option N pour entrer dans le menu interactif a été utilisé (-N) ! Accès au menu interactif !\n", progname);
            break;

          case '?':
            break;

          default:
            fprintf(stderr, "?? getopt returned character code 0%o ??\n", c);
            LOG(LOG_LVL_ERR, "?? getopt returned character code 0%o ??\n", c);

      }
    
    if (v_opt > 2)
      fprintf(stdout,
              "%s: info: curlist = %p [%d, %p]\n",
              progname, curlist,
              curlist ? curlist->N: 0,
              (void*)(curlist ? curlist->next : NULL));
    LOG(LOG_LVL_INFO,
        "%s: info: curlist = %p [%d, %p]\n",
        progname, curlist,
        curlist ? curlist->N: 0,
        (void*)(curlist ? curlist->next : NULL));

    if (A_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info: Appending '%d'\n", progname, arg_elem);
        LOG(LOG_LVL_INFO, "%s: Info: Appending '%d'\n", progname, arg_elem);
        A_opt = 0;
        listechainee_ptr tmplist = append_list(curlist, arg_elem);
        if (tmplist == NULL)
          fprintf(stdout, "%s: Erreur: l'élement '%d' est deja dans la liste\n", progname, arg_elem);
        else
          curlist = tmplist;
      }
    else if (P_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info: Prepending '%d'\n", progname, arg_elem);
        LOG(LOG_LVL_INFO, "%s: Info: Prepending '%d'\n", progname, arg_elem);
        P_opt = 0;
        listechainee_ptr tmplist = prepend_list(curlist, arg_elem);
        if (tmplist == NULL)
          fprintf(stdout, "%s: Erreur: l'élement '%d' est deja dans la liste\n", progname, arg_elem);
        else
          curlist = tmplist;
      }
    else if (d_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info : Affichage de la liste\n", progname);
        LOG(LOG_LVL_INFO, "%s: Info : Affichage de la liste\n", progname);
        d_opt = 0;
        display_list(curlist);
      }
    else if (x_opt || X_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info: Suppression de l'élément à %s de la liste\n", progname, x_opt ? "start" : "end");
        LOG(LOG_LVL_INFO, "%s: Info: Suppression de l'élément à %s de la liste\n", progname, x_opt ? "start" : "end");
        curlist = x_opt ? delete_start_of_list(curlist) : delete_end_of_list(curlist);
        x_opt = X_opt = 0;
      }
    else if (i_opt)
      {
        one_opt = 1;        
        if (v_opt)
          fprintf(stdout, "%s: Info: Initialisation de la liste actuelle !\n", progname);
        LOG(LOG_LVL_INFO, "%s: Info: Initialisation de la liste actuelle !\n", progname);
        init_list();
      }
    else if (l_opt || s_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info: Chargement/enregistrement depuis/vers le nom du fichier '%s'\n", progname, arg_filename);
        LOG(LOG_LVL_INFO, "%s: Info: Chargement/enregistrement depuis/vers le nom du fichier '%s'\n", progname, arg_filename);
        if (l_opt)
          {
            curlist = load_list(arg_filename);
            if (curlist == NULL)
              {
                char msg[ERR_MESSAGE_MAX_SIZE];
                snprintf(msg, ERR_MESSAGE_MAX_SIZE-1, "%s: Erreur: Impossible de charger la liste depuis le fichier '%s'", progname, arg_filename);
                perror(msg);
              }
            else
              if (v_opt)
                fprintf(stdout, "%s: Info: La liste a été chargé avec succès depuis le fichier '%s'\n", progname, arg_filename);
            LOG(LOG_LVL_INFO, "%s: Info: La liste a été chargé avec succès depuis le fichier '%s'\n", progname, arg_filename);
          }
        else if (s_opt)
          {
            if (save_list(curlist, arg_filename) == NULL)
              {
                char msg[ERR_MESSAGE_MAX_SIZE];
                snprintf(msg, ERR_MESSAGE_MAX_SIZE-1, "%s: Erreur: Impossible d'enregistrer la liste dans le fichier '%s'", progname, arg_filename);
                perror(msg);
              }
            else
              if (v_opt)
                fprintf(stdout, "%s: Info: La liste a été sauvegardé avec succès dans le fichier '%s'\n", progname, arg_filename);
            LOG(LOG_LVL_INFO, "%s: Info: La liste a été sauvegardé avec succès dans le fichier '%s'\n", progname, arg_filename);
          }
        l_opt = s_opt = 0;
      }
    else if (t_opt)
      {
        one_opt = 1;
        arg_elem = atoi(optarg);
        if (v_opt)
          fprintf(stdout, "%s: Info: Tester si l'élément '%d' est dans la liste\n", progname, arg_elem);
        LOG(LOG_LVL_INFO, "%s: Info: Tester si l'élément '%d' est dans la liste\n", progname, arg_elem);
        fprintf(stdout, "L'élement '%d' est%s dans la liste.\n", arg_elem, test_elem_in_list(curlist, arg_elem) ? "" : " not");
        LOG(LOG_LVL_INFO, "L'élement '%d' est%s dans la liste.\n", arg_elem, test_elem_in_list(curlist, arg_elem) ? "" : " not");
        t_opt = 0;
      }
    else if (I_opt)
      {
        one_opt = 1;
        if (v_opt)
          fprintf(stdout, "%s: Info: Insertion de l'élément '%d' dans la liste a l'index '%d'\n", progname, arg_elem, arg_index);
        LOG(LOG_LVL_INFO, "%s: Info: Insertion de l'élément '%d' dans la liste a l'index '%d'\n", progname, arg_elem, arg_index);
        curlist = insert_elem_in_list(curlist, arg_index, arg_elem);
        I_opt = 0;
      }
    else if (r_opt)
      {
        one_opt = 1;        
        if (v_opt)
          fprintf(stdout, "%s: Info: Suppression de l'élément '%d' de la liste\n", progname, arg_elem);
        LOG(LOG_LVL_INFO, "%s: Info: Suppression de l'élément '%d' de la liste\n", progname, arg_elem);
        curlist = delete_elem_in_list(curlist, arg_elem);
        r_opt = 0;
      }
    else if (N_opt)
      {
        one_opt = 1;        
      }
  }
  if (one_opt == 0)
    {
      fprintf(stderr, "%s: Erreur: Option invalide, veuillez entrer une option valide:\n", progname);
      LOG(LOG_LVL_ERR, "%s: Erreur: Option invalide, veuillez entrer une option valide:\n", progname);
      print_help();
    }
  else
    {
      if (optind < argc)
        {
          fprintf(stdout, "non-option ARGV-elements: ");
          while (optind < argc)
            fprintf(stdout, "%s ", argv[optind++]);
          fprintf(stdout, "\n");
        }
      else if (h_opt)
        print_help();

      else if (N_opt)
        {
          curlist = enter_interactive_mode(curlist);
          display_list(curlist);
        }
    }

#ifdef DO_LOG
  end_log(logfp);
#endif
  
  return 0;
}
