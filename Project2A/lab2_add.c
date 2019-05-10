#include "imports.c"

void error_out(char *error_msg, int rc) {
  fprintf(stderr, "Error - %s\n", error_msg);
  exit(rc);
}

int main(int argc, char *argv[]){
	struct option options[]= {
		{"threads", required_argument, 0, 't'},
    {"iterations", required_argument, 0, 'i'}
	};

  char opt = -1;
	while((opt=getopt_long(argc, argv, "", options, NULL)) != -1) {
		switch(opt) {
			default:
				error_out("Incorrect argument.", 1);
		}
	}
}