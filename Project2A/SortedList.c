#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element) {
  if (!list || !element) return;
  SortedList_t* tmp = list -> next;
  while (tmp != list && strcmp(element -> key, tmp -> key) > 0)
    tmp = tmp -> next;
  if (opt_yield & INSERT_YIELD)
    sched_yield();
  element -> prev = tmp -> prev;
  element -> next = tmp;
  tmp -> prev -> next = element;
  tmp -> prev = element;
}

int SortedList_delete( SortedListElement_t *element) {
  if (opt_yield & DELETE_YIELD) sched_yield();
  if (element && (element -> prev -> next) && (element -> next -> prev)) {
    element -> prev -> next = element -> next;
    element -> next -> prev = element -> prev;
    return 0;
  } else return 1;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
  if (!list || !key) return NULL;
  SortedListElement_t *tmp = list->next;
  while (tmp != list) {
    if (strcmp(tmp -> key, key) == 0) return tmp;
    if (opt_yield & LOOKUP_YIELD) sched_yield();
    tmp = tmp -> next;
  }
  return NULL;
}

int SortedList_length(SortedList_t *list) {
  if (!list) return -1;
  int counter = 0;
  SortedListElement_t *tmp = list -> next;
  while (tmp != list) {
    if (opt_yield & LOOKUP_YIELD) sched_yield();
    counter++;
    tmp = tmp -> next;
  }
  return counter;
}