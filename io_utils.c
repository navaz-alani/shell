#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// realine reads from the given input stream, until EOF or the `delim` character
// is encountered (whichever happens first). The caller is responsible for
// freeing the returned character array. If the returned pointer is NULL, a
// failure in memory allocation has occurred.
char *readline(FILE *istream, char delim) {
  int ibuffcap = 1, ibufflen = 0;
  char *ibuff = malloc(ibuffcap * sizeof(char));
  char c;
  while (1 == fscanf(istream, "%c", &c)) {
    if (ibufflen == ibuffcap) {
      ibuffcap *= 2;
      char *ibuff_new = realloc(ibuff, ibuffcap * sizeof(char));
      if (!ibuff_new) {
        free(ibuff);
        return NULL;
      }
      ibuff = ibuff_new;
    }
    if ('\n' == c) break;
    else ibuff[ibufflen++] = c;
  }
  ibuff[ibufflen] = '\0';
  return ibuff;
}

char **tokenize(char *s, char *delims) {
  int len = 0, cap = 1;
  char **tokens = malloc(cap * sizeof(char *));
  char **tmp;
  for (char *tok = strtok(s, delims); tok; tok = strtok(NULL, delims)) {
    if (len == cap) {
      cap *= 2;
      tmp = realloc(tokens, cap * sizeof(char *));
      if (!tmp) { free(tokens); return NULL; }
      tokens = tmp;
    }
    tokens[len++] = tok;
  }
  if (len == cap) {
    ++cap;
    tmp = realloc(tokens, cap * sizeof(char *));
    if (!tmp) { free(tokens); return NULL; }
    tokens = tmp;
  }
  tokens[len] = NULL;
  return tokens;
}
