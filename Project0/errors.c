#include <stdio.h>
#include <string.h>

char *unrecognized_argument() {
  char *buf = malloc(1024 * sizeof(char));
  strcpy(buf, "Unrecognized option '%s'. Available options are:\n");
  strcat(buf, "--input (-i) [argument required]\n");
  strcat(buf, "--output (-o) [argument required]\n");
  strcat(buf, "--segfault (-s)\n");
  strcat(buf, "--catch (-c)\n");
  return buf;
}

char *read_input_error() {
  char *buf = malloc(1024 * sizeof(char));
  strcpy(buf, "Could not open input file '%s'!\n");
  strcat(buf, "Error: %s\n");
  return buf;
}

char *redirect_input_error() {
  char *buf = malloc(1024 * sizeof(char));
  strcpy(buf, "Could not redirect stdin!\n");
  strcat(buf, "Error: %s\n");
  return buf;
}

char *create_output_error() {
  char *buf = malloc(1024 * sizeof(char));
  strcpy(buf, "Could not create output file '%s'!\n");
  strcat(buf, "Error: %s\n");
  return buf;
}

char *redirect_output_error() {
  char *buf = malloc(1024 * sizeof(char));
  strcpy(buf, "Could not redirect stdout!\n");
  strcat(buf, "Error: %s\n");
  return buf;
}
