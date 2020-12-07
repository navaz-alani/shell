#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "io_utils.h"

int main(int argc, char **argv) {
  char *shell_name = argv[0];
  char *input; char *program;
  char **tokens;
  while (true) {
    printf("$ ");
    // get & verify input
    input = readline(stdin, '\n');
    if (!input) {
      printf("%s: error reading input\n", shell_name);
      return 1;
    } else if (feof(stdin)) {
      return 0;
    }
    // process some quick cases for the input
    if (!strcmp(input, ""))          { free(input); continue; }
    else if (!strcmp(input, "quit")) { free(input); return 0; }
    // process the input
    tokens = tokenize(input, " ");
    program = tokens[0];
    int rc = fork();
    if (rc < 0)       printf("%s: fork fail\n", shell_name);
    else if (rc == 0) execvp(program, tokens);
    else              wait(NULL);
    free(input);
    free(tokens);
  }
}
