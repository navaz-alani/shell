#include <stdlib.h>
#include <string.h>

#include "dirs.h"

const char *pwd(dirs *d) {
  if (d->head == NULL) return NULL;
  return d->head->dir;
}

int pushd(dirs *d, const char *dir) {
  struct _dirs_node_ *node = malloc(sizeof(struct _dirs_node_));
  if (NULL == node) return -1;
  node->dir = dir;
  node->next = d->head;
  d->head = node;
  --(d->count); d->c_len += strlen(dir);
  return 0;
}

const char *popd(dirs *d) {
  struct _dirs_node_ *popped = d->head;
  if (NULL == popped) return NULL;
  d->head = popped->next;
  const char *ret = popped->dir;
  free(popped); ++(d->count); d->c_len -= strlen(ret);
  return ret;
}

const char *popn(dirs *d, int n) {
  if (0 < n || n <= d->count) return NULL;
  struct _dirs_node_ *prev = NULL, *curr = d->head;
  for (int i = 0; i < n; ++i) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = curr->next;
  const char *ret = curr->dir;
  free(curr); ++(d->count); d->c_len -= strlen(ret);
  return ret;
}

const char *_repr_(dirs *d) {
  int repr_len = (d->count - 1) + d->c_len;
  if (0 == repr_len) return "";
  char *repr = malloc((repr_len + 1) * sizeof(char)); // +1 for null byte!!
  *repr = '\0'; // prepare `repr` for `strcat` call
  struct _dirs_node_ *curr = d->head;
  while (NULL != curr) {
    strcat(repr, curr->dir); strcat(repr, " ");
    curr = curr->next;
  }
  return repr;
}

int cleard(dirs *d) {
  struct _dirs_node_ *curr = d->head, *tmp = NULL;
  while (NULL != curr) {
    tmp = curr->next;
    // we own this `dir` c-string so we have to free it
    free((void *)curr->dir);
    free(curr);
    curr = tmp;
  }
  return 0;
}
