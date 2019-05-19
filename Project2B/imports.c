#ifndef IMPORTS
#define IMPORTS
  #include <getopt.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
  #include <time.h>
  #include <math.h>
  #include <string.h>

  void error_out(char *error_msg, int rc) {
    fprintf(stderr, "Error - %s\n", error_msg);
    exit(rc);
  }

  long long timespec_diff(
    struct timespec start,
    struct timespec stop
  ){
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
  
#endif