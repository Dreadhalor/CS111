#include "SortedList.h"
#include "imports.c"

int n_threads = 1;
int iterations = 1;
int yieldFlag = 0;

SortedListElement_t* elements;
SortedList_t* lists;
int n_sublists = 1;

pthread_mutex_t *mutexes;
char sync_flag = 0;
int *spinlocks;
long long *lock_times;

int opt_yield = 0;
char opt_tag[100] = "-";

//int last_hash;
int hash(char key) {
  int result = key % n_sublists;
  /*if (last_hash != result){
    last_hash = result;
    printf("Hash is %i\n", result);
  }*/
  return result;
}

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

  struct timespec lockStartTime;
  struct timespec lockEndTime;

  //Insert
  int start = *((int*) ptr);
  for (int i = start; i < start + iterations; i++) {
    int sublist = hash(elements[i].key[0]);
    switch(sync_flag){
      case 'm': {
        clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
        pthread_mutex_lock(&mutexes[sublist]);
        clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
        lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
        SortedList_insert(&lists[sublist], &elements[i]);
        pthread_mutex_unlock(&mutexes[sublist]);
        break;
      }
      case 's': {
        clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
        while (__sync_lock_test_and_set(&spinlocks[sublist], 1)) {
          continue;
        }
        clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
        lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
        SortedList_insert(&lists[sublist], &elements[i]);
        __sync_lock_release(&spinlocks[sublist]);
        break;
      }
      default:
        SortedList_insert(&lists[sublist], &elements[i]);
        break;
    }
  }
  
  //Length
  int len = 0;
  int rand_index = rand() % n_sublists;
  switch(sync_flag){
    case 'm': {
      clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
      pthread_mutex_lock(&mutexes[rand_index]);
      clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
      lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
      len = SortedList_length(&lists[rand_index]);
      pthread_mutex_unlock(&mutexes[rand_index]);
      break;
    }
    case 's': {
      clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
      while (__sync_lock_test_and_set(&spinlocks[rand_index], 1)) {
        continue;
      }
      clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
      lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
      len = SortedList_length(&lists[rand_index]);
      __sync_lock_release(&spinlocks[rand_index]);
      break;
    }
    default:
      len = SortedList_length(&lists[rand_index]);
      break;
  }
  if (len < 0) error_out("List length is negative", 2);

  //Lookup
  SortedListElement_t* toDelete;
  for (int i = start; i < start + iterations; i++) {
    int sublist = hash(elements[i].key[0]);
    switch(sync_flag){
      case 'm': {
        clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
        pthread_mutex_lock(&mutexes[sublist]);
        clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
        lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
        toDelete = SortedList_lookup(&lists[sublist], elements[i].key);
        if (SortedList_delete(toDelete))
          fprintf(stderr, "Error: could not delete list element!\n");
        pthread_mutex_unlock(&mutexes[sublist]);
        break;
      }
      case 's': {
        clock_gettime(CLOCK_MONOTONIC, &lockStartTime);
        while (__sync_lock_test_and_set(&spinlocks[sublist], 1)) {
          continue;
        }
        clock_gettime(CLOCK_MONOTONIC, &lockEndTime);
        lock_times[start/iterations] += timespec_diff(lockStartTime,lockEndTime);
        toDelete = SortedList_lookup(&lists[sublist], elements[i].key);
        if (SortedList_delete(toDelete))
          fprintf(stderr, "Error: could not delete list element!\n");
        __sync_lock_release(&spinlocks[sublist]);
        break;
      }
      default:
        toDelete = SortedList_lookup(&lists[sublist], elements[i].key);
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
    {"lists", required_argument, 0, 'l'},
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
        break;
      case 'l':
        n_sublists = atoi(optarg);
        break;
      default:
        error_out("Incorrect argument.", 1);
        break;
    }
  }
  if (strlen(opt_tag) == 1) strcat(opt_tag, "none");

  //initialize lists
  lists = malloc(n_sublists * sizeof(SortedList_t));
  for (int i = 0; i < n_sublists; i++) {
    lists[i].key = NULL;
    lists[i].next = &lists[i];
    lists[i].prev = &lists[i];
  }

  int n_elements = n_threads * iterations;
  elements = malloc(n_elements * sizeof(SortedListElement_t));
  srand((unsigned int) time(NULL));
  for (int i = 0; i < n_elements; i++){
    char* key = malloc(2 * sizeof(char));
    key[0] = 'A' + (rand()%26);
    key[1] = 0;
    elements[i].key = key;
  }

  // initialize mutexes
  mutexes = malloc(n_sublists * sizeof(pthread_mutex_t));
  if (sync_flag == 'm') {
    for (int i = 0; i < n_sublists; i++) {
      pthread_mutex_init(&mutexes[i], NULL);
    }
  }

  // initialize spinlocks
  spinlocks = malloc(n_sublists * sizeof(int));
  if (sync_flag == 's') {
    for (int i = 0; i < n_sublists; i++) {
      spinlocks[i] = 0;
    }
  }

  // initialize thread lock times
  lock_times = malloc(sizeof(long long) * n_threads);
	
  struct timespec t_start, t_end;
  clock_gettime(CLOCK_MONOTONIC, &t_start);

  pthread_t threads[n_threads];
  int thread_data[n_threads];
  for (int i = 0; i < n_threads; i++){
    thread_data[i] = i * iterations;
    pthread_create(&threads[i], NULL, iterate, &thread_data[i]);
  }
  for (int i = 0; i < n_threads; i++)
    pthread_join(threads[i], NULL);

  clock_gettime(CLOCK_MONOTONIC, &t_end);

  // get total lock time
  long long total_lock_time = 0;
  for (int i = 0; i < n_threads; i++) {
    total_lock_time += lock_times[i]; 
  }

  int len = 0;
  for (int i = 0; i < n_sublists; i++)
    len += SortedList_length(&lists[i]);
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
  printf("%s,%i,%i,%i,%i,%lld,%lld,%llu\n",
    buffer,
    n_threads,
    iterations,
    n_sublists,
    n_ops,
    runtime,
    runtime/n_ops,
    total_lock_time/n_ops
  );

  free(lock_times);
  free(lists);
  for (int i = 0; i < n_elements; i++)
    free((char*) elements[i].key);
  free(elements);
  free(mutexes);
  free(spinlocks);

  exit(0);
}