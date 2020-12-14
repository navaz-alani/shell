#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#include "io_utils.h"
#include "shell.h"
#include "builtins.h"
#include "globbing.h"

void free_globbed_tokens(char **tokens, int num_tokens) {
  for (int i = 0; i < num_tokens; ++i) free(tokens[i]);
}

int read_eval(shell *sh) {
  char *input; char *program;
  char **tokens; int num_tokens = 0;
  char *tmp;
  // prompt printed to users
  char prompt[PATH_MAX + 11];
  // begin read-eval loop
  while (true) {
    sprintf(prompt, "[pwd: %s]\n$ ", sh->pwd);
    printf("%s", prompt);
    // get & verify input
    input = readline(stdin, '\n');
    if (0 == input) {
      printf("%s: error reading input\n", sh->name);
      return 1;
    } else if (feof(stdin)) return 0;
    // tokenize input
    tokens = esc_tokenize(input, " ", '\\', &num_tokens);
    for (int i = 0; i < num_tokens; ++i) {
      tmp = glob_token(tokens[i]);
      if (NULL == tmp)
        printf("%s: glob fail for token \"%s\"\n", sh->name, tokens[i]);
      else
        tokens[i] = tmp;
    }
    // handle command if it is bultin
    if (0 == handle_builtin(sh, tokens, num_tokens)) {
      free_globbed_tokens(tokens, num_tokens); free(tokens); free(input);
      // if the shell's `done` flag is set, exit
      if (sh->done) return 0;
      else continue;
    }
    // process the input
    program = tokens[0];
    int rc = fork();
    if (rc < 0) {
      printf("%s: fork fail\n", sh->name); perror("err");
    } else if (0 == rc) {
      execvp(program, tokens);
      // exec failed - notify error & kill forked child
      printf("%s exec fail\n", sh->name); perror("err");
      kill(getpid(), SIGTERM);
    } else wait(NULL);
    // cleanup
    free_globbed_tokens(tokens, num_tokens); free(input); free(tokens);
  }
}
