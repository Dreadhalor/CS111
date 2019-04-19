#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "errors.c"

#define INPUT     'i'
#define OUTPUT    'o'
#define SEGFAULT  's'
#define CATCH     'c'

void handler(int signum) {
  fprintf(stderr, "Caught segmentation fault! Signal number: %d\n", signum);
  exit(4);
}
 
int main(int argc, char *argv[]) {
  int opt_index = 0;
  int segfault = 0;

  struct option long_options[] = {
    {"input", required_argument, NULL, INPUT},
    {"output", required_argument, NULL, OUTPUT},
    {"segfault", no_argument, NULL, SEGFAULT},
    {"catch", no_argument, NULL, CATCH},
    {0, 0, 0, 0}
  };

  while (1) {
    int arg = getopt_long(argc, argv, "i:o:sc", long_options, &opt_index);
    if (arg == -1) break;

    switch (arg) {
      case INPUT: {
        //attempt to open input
        int inputfd = open(optarg, O_RDONLY);
        if (inputfd == -1) {
          //Could not open input file
          fprintf(stderr, read_input_error(), optarg, strerror(errno));
          exit(2);
        } else if (dup2(inputfd, STDIN_FILENO) == -1) {
          //Could not redirect stdin
          fprintf(stderr, redirect_input_error(), strerror(errno));
          exit(2);
        }
        break;
      }
      case OUTPUT: {
        //redirect output if file can be created
        int outputfd = creat(optarg, 0644);
        if (outputfd == -1) {
          //Could not create output file
          fprintf(stderr, create_output_error(), optarg, strerror(errno));
          exit(3);
        } else if (dup2(outputfd, STDOUT_FILENO) == -1) {
          //Could not redirect stdout
          fprintf(stderr, redirect_output_error(), strerror(errno));
          exit(3);
        }
        break;
      }
      case SEGFAULT:
        //set segfault flag
        segfault = 1;
        break;
      case CATCH:
        //set segfault handler
        signal(SIGSEGV, handler);
        break;
      default: {
        fprintf(stderr, unrecognized_argument(), argv[optind-1]);
        exit(1);
      }
    }
  }

  //segfault
  int *segfault_trigger = NULL;
  if (segfault) *segfault_trigger = 1;
  
  //read + write bytes
  int buffer_size = 1024;
  int rbytes, wbytes;
  char buf[buffer_size+1];

  do {
    rbytes = read(STDIN_FILENO, &buf, buffer_size);
    if (rbytes == -1) {
      fprintf(stderr, "Error reading from stdin!");
      exit(2);
    }
    wbytes = write(STDOUT_FILENO, &buf, rbytes);
    if (wbytes == -1) {
      fprintf(stderr, "Error writing to stdout!\n");
      exit(3);
    }
  } while (rbytes > 0);

  //exit on success
  exit(0);

}