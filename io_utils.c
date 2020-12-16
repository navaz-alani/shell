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

bool __is_in_str__(const char *str, char c) {
  while (*str!= '\0')
    if (c == *(str++)) return true;
  return false;
}

char **esc_tokenize(char *s, char *delims, char esc, int *num_tokens) {
  int len = 0, cap = 1;
  char **tokens = malloc(cap * sizeof(char *));
  bool escape = false;
  // initialize tok_start to first non-delim character
  char *tok_start = NULL;
  while ('\0' != *s) {
    if (*s == esc) escape = true;
    else if (__is_in_str__(delims, *s)) {
      if (escape) {
        if (NULL == tok_start) tok_start = s;
        escape = false;
        ++s;
      } else {
        *s = '\0';
        if (NULL == tok_start) { ++s; continue; }
        // here we grow using the doubling strategy for amortized O(n)
        // time complexity
        if (len == cap && __grow_str_buff__(&tokens, cap *= 2)) return NULL;
        tokens[len++] = tok_start;
        tok_start = ++s;
      }
      continue;
    } else if (NULL == tok_start) {
      tok_start = s;
    }
    ++s;
  }
  // here we grow by an absolute amount of 2
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

int __l_strip_str__(const char *str, const char *strip) {
  int i = 0;
  while ('\0' != *(str + i))
    if (!__is_in_str__(strip, *(str + i))) ++i;
    else break;
  return i;
}

int __r_strip_str__(const char *str, const char *strip) {
  int i = strlen(str) - 1;
  while (i >= 0)
    if (!__is_in_str__(strip, *(str + i))) --i;
    else break;
  if (i == -1) return 0;
  return i;
}

char *__strip_str__(char *str, const char *strip) {
  // do not need to modify all of the right strip characters to null bytes, just
  // the first one
  int l_str_len = __l_strip_str__(str, strip);
  int r_str_len = __r_strip_str__(str, strip);
  // check if whole string is stripped
  if (r_str_len < l_str_len) { *str = '\0'; return str; }
  *(str + __r_strip_str__(str, strip)) = '\0';
  return str + __l_strip_str__(str, strip);
}
