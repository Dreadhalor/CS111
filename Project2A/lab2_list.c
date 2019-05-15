#include "SortedList.h"
#include "imports.c"

int n_threads = 1;
int iterations = 1;
int yieldFlag = 0;

SortedListElement_t* elements;
SortedList_t* list;

pthread_mutex_t mutex;
char sync_flag = 0;
volatile int spinlock = 0;

int opt_yield = 0;
char opt_tag[5] = "-";

char *get_tags(char *buffer, char *opt_tag, char sync_flag){
  char *format = "list%s%s";
  char *sync_val = "";
  switch (sync_flag){
    case 'm':
      sync_val = "-m";
      break;
    case 's':
      sync_val = "-s";
      break;
    default:
      sync_val = "-none";
      break;
  }
  sprintf(buffer, format, opt_tag, sync_val);
  return buffer;
}

void* iterate(void* ptr) {
  int start = *((int*) ptr);
  for (int i = start; i < start + iterations; i++) {
    switch(sync_flag){
      case 'm': {
        pthread_mutex_lock(&mutex);
        SortedList_insert(list, &elements[i]);
        pthread_mutex_unlock(&mutex);
        break;
      }
      case 's': {
        while (__sync_lock_test_and_set(&spinlock, 1)) {
          while(spinlock);
        }
        SortedList_insert(list, &elements[i]);
        __sync_lock_release(&spinlock);
        break;
      }
      default:
        SortedList_insert(list, &elements[i]);
        break;
    }
  }
  
  int len = 0;
  switch(sync_flag){
    case 'm': {
      pthread_mutex_lock(&mutex);
      len = SortedList_length(list);
      pthread_mutex_unlock(&mutex);
      break;
    }
    case 's': {
      while (__sync_lock_test_and_set(&spinlock, 1)) {
        while(spinlock);
      }
      len = SortedList_length(list);
      __sync_lock_release(&spinlock);
      break;
    }
    default:
      len = SortedList_length(list);
      break;
  }
  if (len < 0) error_out("List length is negative", 2);

  SortedListElement_t* toDelete;
  for (int i = start; i < start + iterations; i++) {
    switch(sync_flag){
      case 'm': {
        pthread_mutex_lock(&mutex);
        toDelete = SortedList_lookup(list, elements[i].key);
        if (SortedList_delete(toDelete))
          fprintf(stderr, "Error: could not delete list element!\n");
        pthread_mutex_unlock(&mutex);
        break;
      }
      case 's': {
        while (__sync_lock_test_and_set(&spinlock, 1)) {
          while(spinlock);
        }
        toDelete = SortedList_lookup(list, elements[i].key);
        if (SortedList_delete(toDelete))
          fprintf(stderr, "Error: could not delete list element!\n");
        __sync_lock_release(&spinlock);
        break;
      }
      default:
        toDelete = SortedList_lookup(list, elements[i].key);
        if (SortedList_delete(toDelete))
          fprintf(stderr, "Error: could not delete list element!\n");
        break;
    }
  }
  
  return NULL;
}

int main(int argc, char **argv){

  struct option long_options[] = {
    {"threads", required_argument, 0, 't'},
    {"iterations", required_argument, 0, 'i'},
    {"yield", required_argument, 0, 'y'},
    {"sync", required_argument, 0, 's'},
    {0, 0, 0, 0}
  };

  char opt = -1;
	while((opt=getopt_long(argc, argv, "", long_options, NULL)) != -1) {
		switch(opt) {
      case 't':
        n_threads = atoi(optarg);
        break;
      case 'i':
        iterations = atoi(optarg);
        break;
      case 'y': {
        int len = strlen(optarg);
        if (len > 3) error_out("Too many arguments for --yield", 1);
        for (int i = 0; i < len; i++) {
          char sync_opt = optarg[i];
          switch(sync_opt){
            case 'i':
              opt_yield |= INSERT_YIELD;
              strcat(opt_tag, "i");
              break;
            case 'd':
              opt_yield |= DELETE_YIELD;
              strcat(opt_tag, "d");
              break;
            case 'l':
              opt_yield |= LOOKUP_YIELD;
              strcat(opt_tag, "l");
              break;
            default: {
              char buffer[100];
              sprintf(buffer, "Invalid argument '%c' for --yield", sync_opt);
              error_out(buffer, 1);
              break;
            }
          }
        }
        break;
      }
      case 's':
        sync_flag = *optarg;
        if (sync_flag == 'm')
          pthread_mutex_init(&mutex, NULL);
        break;
      default:
        error_out("Incorrect argument.", 1);
        break;
    }
  }
  if (strlen(opt_tag) == 1) strcat(opt_tag, "none");

  list = malloc(sizeof(SortedList_t));
  list->key = NULL;
  list->next = list->prev = list;
  int n_elements = n_threads * iterations;
  elements = malloc(n_elements * sizeof(SortedListElement_t));
  srand((unsigned int) time(NULL));
  for (int i = 0; i < n_elements; i++){
    char key[2];
    key[0] = 'A' + (rand()%26);
    key[1] = 0;
    elements[i].key = key;
  }
	
  struct timespec t_start, t_end;
  clock_gettime(CLOCK_REALTIME, &t_start);

  pthread_t threads[n_threads];
  int thread_data[n_threads];
  for (int i = 0; i < n_threads; i++){
    thread_data[i] = i * iterations;
    pthread_create(&threads[i], NULL, iterate, &thread_data[i]);
  }
  for (int i = 0; i < n_threads; i++)
    pthread_join(threads[i], NULL);

  clock_gettime(CLOCK_REALTIME, &t_end);

  int len = SortedList_length(list);
  if (len > 0) {
    char buffer[100];
    sprintf(buffer, "List is not empty. Length: %i", len);
    error_out(buffer, 2);
  }
  if (len < 0) error_out("List length is negative", 2);
	
  int n_ops = n_threads * iterations * 3;
  long long runtime = timespec_diff(t_start,t_end);

  char buffer[100];
  get_tags(buffer, opt_tag, sync_flag);
  printf("%s,%i,%i,1,%i,%lld,%lld\n",
    buffer,
    n_threads,
    iterations,
    n_ops,
    runtime,
    runtime/n_ops
  );

  free(list);
  free(elements);

  exit(0);
}