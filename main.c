#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <limits.h>
#include <execinfo.h>
#include <stdlib.h>

#include "shell.h"
#include "io_utils.h"

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char **argv) {
  signal(SIGSEGV, handler);   // install segv handler
  shell sh;
  sh.name = argv[0];
  sh.done = false;
  // initialize pwd
  char pwd[PATH_MAX];
  if (getcwd(pwd, sizeof(pwd)) != NULL) sh.pwd = pwd;
  else { perror("init: getcwd() error"); return 1; }
  // start shell
  return read_eval(&sh);
}
