#include <stdlib.h>
#include <glob.h>

#include "io_utils.h"

char *glob_token(char *tok) {
  glob_t gbuff;
  gbuff.gl_offs = 0;
  glob(tok, GLOB_TILDE | GLOB_BRACE | GLOB_DOOFFS | GLOB_NOCHECK, NULL, &gbuff);
  char *ret = __concat_str__(gbuff.gl_pathv, gbuff.gl_pathc, " ");
  free(gbuff.gl_pathv);
  if (NULL == ret) return NULL;
  return ret;
}
