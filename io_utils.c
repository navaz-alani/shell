#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int __grow_str_buff__(char ***buff, int new_cap) {
  char **tmp = realloc(*buff, new_cap * sizeof(char *));
  if (NULL == tmp) return -1;
  *buff = tmp;
  return 0;
}

// is_delim determines whether the character `c` is in the deliters `delims`.
bool is_delim(char *delims, char c) {
  while (*delims != '\0')
    if (c == *(delims++)) return true;
  return false;
}

char **esc_tokenize(char *s, char *delims, char esc, int *num_tokens) {
  int len = 0, cap = 1;
  char **tokens = malloc(cap * sizeof(char *));
  bool escape = false;
  char *tok_start = s;
  while ('\0' != *s) {
    if (*s == esc) escape = true;
    else if (is_delim(delims, *s)) {
      if (escape) {
        escape = false;
        ++s;
      } else {
        *s = '\0';
        if (len == cap && __grow_str_buff__(&tokens, cap *= 2)) return NULL;
        tokens[len++] = tok_start;
        tok_start = ++s;
      }
      continue;
    }
    ++s;
  }
  if (len == cap && __grow_str_buff__(&tokens, cap + 2)) return NULL;
  tokens[len++] = tok_start;
  tokens[len] = NULL; // terminate token array (for exec calls)
  *num_tokens = len;
  return tokens;
}

char *__concat_str__(char **parts, int num_parts, char *sep) {
  // first compute length of concatenated c-string
  int joint_len = 0;
  for (int i = 0; i < num_parts; ++i) joint_len += strlen(parts[i]);
  joint_len += (num_parts - 1) * strlen(sep);
  joint_len += 1; // for null byte
  char *joint = malloc(joint_len * sizeof(char));
  joint[0] = '\0'; // prepare `joint` for use with `strcat`
  for (int i = 0; i < num_parts; ++i) {
    strcat(joint, parts[i]);
    if (i != num_parts - 1) strcat(joint, sep);
  }
  return joint;
}
