#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "list/list.h"
#define BUFFER_MAX_SIZE 		  20
extern listechainee_ptr curlist;
extern char* progname;



int lenlist(struct listechainee_st *list) {
    int len = 0;
    struct listechainee_st *current = list;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void free_list(listechainee_ptr list) {
    while (list != NULL) {
        listechainee_ptr tmp = list;
        list = list->next;
        free(tmp);
    }
}

void init_list(void) {
    free_list(curlist);
    curlist = NULL;
}

listechainee_ptr reinit_list(listechainee_ptr list) {
    init_list();
    curlist = list;
    return curlist;
}

void display_list(listechainee_ptr list)
{
    if (list == NULL)
    {
        printf("Liste vide\n");
    }
    else
    {
        printf("Liste: [");
        while (list != NULL)
        {
            printf("%d", list->N);
            if (list->next != NULL)
            {
                printf(",");
            }
            list = list->next;
        }
        printf("]\n");
    }
}

listechainee_ptr
load_list(char* filename)
{
  listechainee_ptr list = reinit_list(curlist);
  FILE *fp = fopen(filename, "r");
  if (fp == (FILE*)NULL)
      return NULL;
  else
    {
      char s[BUFFER_MAX_SIZE];
      char* s_ptr = (char*)NULL;
      char* e_ptr = (char*)NULL;
      while ((s_ptr = fgets(s, BUFFER_MAX_SIZE-1, fp)) != (char*)NULL)
        {
          do
            {
              int n = (int)strtol(s_ptr, &e_ptr, 10);
              if (*e_ptr == ',')
                s_ptr = e_ptr+1;
              else
                s_ptr = e_ptr;
              list = append_list(list, n);
            }
          while(*s_ptr != '\n' && *s_ptr != EOF);
        }
    }
  return list;
}

listechainee_ptr
save_list(listechainee_ptr list, char* filename)
{
  FILE *fp = fopen(filename, "w");
  if (fp == (FILE *)NULL)
      return NULL;
  else
    {
      listechainee_ptr tmp = list;
      while (tmp)
        {
          fprintf(fp, "%d", tmp->N);
          if (tmp->next)
            fprintf(fp, ",");
          tmp = tmp->next;
        }
      fprintf(fp, "\n");
      fclose(fp);
    }
  return list;
}

int test_elem_in_list(listechainee_ptr list, int n)
{
    while (list != NULL)
    {
        if (list->N == n)
        {
            return TRUE;
        }
        list = list->next;
    }
    return FALSE;
}

int test_ix_in_list(listechainee_ptr list, int ix)
{
    if (ix < 0)
    {
        return FALSE;
    }
    int current_ix = 0;
    listechainee_ptr tmp = list;
    while (tmp != NULL)
    {
        if (current_ix == ix)
        {
            return TRUE;
        }
        tmp = tmp->next;
        current_ix++;
    }
    return FALSE;
}

listechainee_ptr append_list(listechainee_ptr list, int n)
{
    listechainee_ptr new_node = (listechainee_ptr)malloc(sizeof(struct listechainee_st));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le nouveau nœud.\n");
        return list;
    }
    new_node->N = n;
    new_node->next = NULL;
    if (list == NULL) {
        list = new_node;
    } else {
        listechainee_ptr tmp = list;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    return list;
}

listechainee_ptr prepend_list(listechainee_ptr list, int n)
{
    listechainee_ptr new_node = (listechainee_ptr)malloc(sizeof(struct listechainee_st));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le nouveau nœud.\n");
        return list;
    }
    new_node->N = n;
    new_node->next = list;
    return new_node;
}

listechainee_ptr insert_elem_in_list(listechainee_ptr list, int ix, int n)
{
    if (!test_ix_in_list(list, ix) || test_elem_in_list(list, n)) {
        return list;
    }
    listechainee_ptr new_node = (listechainee_ptr)malloc(sizeof(struct listechainee_st));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le nouveau nœud.\n");
        return list;
    }
    new_node->N = n;
    new_node->next = NULL;
    if (ix == 0) {
        new_node->next = list;
        return new_node;
    }
    int current_ix = 0;
    listechainee_ptr current = list;
    while (current->next != NULL && current_ix < ix - 1) {
        current = current->next;
        current_ix++;
    }
    new_node->next = current->next;
    current->next = new_node;
    return list;
}

int find_elem_ix(listechainee_ptr list, int n)
{
    int ix = -1;
    while (list != NULL)
    {
        ix++;
        if (list->N == n)
        {
            return ix;
        }
        list = list->next;
    }
    return -1;
}

listechainee_ptr delete_end_of_list(listechainee_ptr list)
{
    if (list == NULL || list->next == NULL) {
        free(list);
        return NULL;
    }
    listechainee_ptr current = list;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return list;
}

listechainee_ptr delete_start_of_list(listechainee_ptr list)
{
    if (list == NULL) {
        return NULL;
    }
    listechainee_ptr new_head = list->next;
    free(list);
    return new_head;
}

listechainee_ptr delete_elem_in_list(listechainee_ptr list, int n)
{
    if (list == NULL) {
        return NULL;
    }
    if (list->N == n) {
        listechainee_ptr temp = list;
        list = list->next;
        free(temp);
        return list;
    }
    listechainee_ptr current = list->next;
    listechainee_ptr previous = list;
    while (current != NULL) {
        if (current->N == n) {
            previous->next = current->next;
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
    return list;
}