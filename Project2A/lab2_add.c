#include "imports.c"

#define YIELD 0;

void error_out(char *error_msg, int rc) {
  fprintf(stderr, "Error - %s\n", error_msg);
  exit(rc);
}

long long global_counter = 0;

struct thread_data{
   int thread_id;
   int iterations;
   long long *counter;
};

char *tags[] = {
  "add-none",
  "add-yield-none"
};

char *get_tags(char *buffer, int yield, char sync_flag){
  char *format = "add%s%s";
  char *yield_val = yield ? "-yield" : "";
  char *sync_val = "";
  switch (sync_flag){
    case 'c':
      sync_val = "-c";
      break;
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
  sprintf(buffer, format, yield_val, sync_val);
  return buffer;
}

long long timespec_diff(
  struct timespec start,
  struct timespec stop){
  struct timespec result;
  long long val = 0;
  if ((stop.tv_nsec - start.tv_nsec) < 0) {
    result.tv_sec = stop.tv_sec - start.tv_sec - 1;
    result.tv_nsec = stop.tv_nsec - start.tv_nsec + 1000000000;
  } else {
    result.tv_sec = stop.tv_sec - start.tv_sec;
    result.tv_nsec = stop.tv_nsec - start.tv_nsec;
  }
  return val + result.tv_nsec + result.tv_sec*pow(10,9);
}

int opt_yield = 0;
void add(long long *pointer, long long value) {
  long long sum = *pointer + value;
  if (opt_yield) sched_yield();
  *pointer = sum;
}

pthread_mutex_t mutex;
char sync_flag = 0;
void add_sync_m(long long *pointer, long long value){
  pthread_mutex_lock(&mutex);
	add(pointer, value);
	pthread_mutex_unlock(&mutex);
}

volatile int spinlock = 0;
void add_sync_s(long long *pointer, long long value){
  while (__sync_lock_test_and_set(&spinlock, 1)) {
    while (spinlock);
  }
  add(pointer, value);
  __sync_lock_release(&spinlock);
}

void add_sync_c(long long *pointer, long long value){
  long long sum_i, sum_f;
  do {
    sum_i = __sync_val_compare_and_swap(pointer, 0, 0);
    sum_f = sum_i + value;
    if (opt_yield) sched_yield();
  } while(__sync_val_compare_and_swap(pointer, sum_i, sum_f) != sum_i);
}

void iterate(void *ptr){
  struct thread_data *data = (struct thread_data *) ptr;
  for (int i = 0; i < data -> iterations; i++){
    if (sync_flag){
      switch(sync_flag){
        case 'm':
          add_sync_m(data -> counter, 1);
          break;
        case 's':
          add_sync_s(data -> counter, 1);
          break;
        case 'c':
          add_sync_c(data -> counter, 1);
          break;
      }
    } else add(data -> counter, 1);
  }
  for (int i = 0; i < data -> iterations; i++)
    if (sync_flag){
      switch(sync_flag){
        case 'm':
          add_sync_m(data -> counter, -1);
          break;
        case 's':
          add_sync_s(data -> counter, -1);
          break;
        case 'c':
          add_sync_c(data -> counter, -1);
          break;
      }
    } else add(data -> counter, -1);
}

int main(int argc, char *argv[]){
	struct option options[]= {
		{"threads", required_argument, 0, 't'},
    {"iterations", required_argument, 0, 'i'},
    {"yield", no_argument, 0, 'y'},
    {"sync,", required_argument, 0, 's'},
    {0,0,0,0}
	};
  int iterations = 0;
  int n_threads = 0;

  char opt = -1;
	while((opt=getopt_long(argc, argv, "", options, NULL)) != -1) {
		switch(opt) {
      case 'i':
        iterations = atoi(optarg);
        break;
      case 't':
        n_threads = atoi(optarg);
        break;
      case 'y':
        opt_yield = 1;
        break;
      case 's': {
        int len = strlen(optarg);
        if (len > 1){
          char buffer[50 + len];
          sprintf(buffer, "Invalid argument '%s' for --sync", optarg);
          error_out(buffer, 1);
        }
        if (len == 1){
          char sync_opt = optarg[0];
          switch(sync_opt){
            case 'm':
              sync_flag = 'm';
              pthread_mutex_init(&mutex, NULL);
              break;
            case 's':
              sync_flag = 's';
              break;
            case 'c':
              sync_flag = 'c';
              break;
            default: {
              char buffer[50];
              sprintf(buffer, "Invalid argument '%c' for --sync", sync_opt);
              error_out(buffer, 1);
            }
          }
        } else error_out("Argument required for option --sync", 1);
        break;
      }
			default:
				error_out("Incorrect argument.", 1);
		}
	}

  if (iterations > 0 && n_threads > 0){
    pthread_t threads[n_threads];
    struct thread_data data[n_threads];

    struct timespec t_start, t_end;
    clock_gettime(CLOCK_REALTIME, &t_start);

    for(int i = 0; i < n_threads; i++){
      data[i].thread_id = i;
      data[i].iterations = iterations;
      data[i].counter = &global_counter;
      pthread_create(&threads[i], NULL, (void *)&iterate, &data[i]);
    }
    for (int i = 0; i < n_threads; i++)
      pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_REALTIME, &t_end);
    int n_ops = n_threads * iterations * 2;
    long long runtime = timespec_diff(t_start,t_end);
    char tag[50];
    get_tags(tag, opt_yield, sync_flag);

    printf("%s,%i,%i,%i,%lld,%lld,%lld\n",
      tag,
      n_threads,
      iterations,
      n_ops,
      runtime,
      runtime/n_ops,
      global_counter
    );

    pthread_exit(NULL);
  }
  exit(0);
}