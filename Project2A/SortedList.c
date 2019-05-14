#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element);
int SortedList_delete(SortedListElement_t *element);
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key);
int SortedList_length(SortedList_t *list);