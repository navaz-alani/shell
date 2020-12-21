#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "io_utils.h"

// default delimiters
const char *ws = " \t";

/*
 * TOKENIZER UTILITY TESTS
 **/

// `esc_tokenize_test` is a test for the tokenizer utility.
typedef struct _esc_tokenize_test_ {
  char *str;
  int tokc;
  char **tokv;
} esc_tokenize_test;

// `run_esc_tokenize_test` runs the tokenizer test given.
void run_esc_tokenize_test(const esc_tokenize_test *tst) {
  int num_tokens;
  char **tokens = esc_tokenize(tst->str, ws, '\\', &num_tokens);
  // perform the test
  assert(num_tokens == tst->tokc);
  for (int i = 0; i < tst->tokc; ++i) assert(!strcmp(tokens[i], tst->tokv[i]));
  // free memory associated with test
  free(tst->str); free(tokens);
}

// `test_esc_tokenize` orchestrates the tokenizer utility tests.
void test_esc_tokenize() {
  esc_tokenize_test t1;
  // need strdup to prevent EXC_BAD_ACCESS since the `str` field is modified
  t1.str = strdup("echo 1 2 3"); t1.tokc = 4;
  t1.tokv = (char *[4]){"echo", "1", "2", "3"};

  esc_tokenize_test t2;
  t2.str = strdup("\t\t  \t echo  \t  \t 1 \t   2    3    "); t2.tokc = 4;
  t2.tokv = (char *[4]){"echo", "1", "2", "3"};

  esc_tokenize_test t3;
  t3.str = strdup(" \t d          \t  \t"); t3.tokc = 1;
  t3.tokv = (char *[1]){"d"};

  esc_tokenize_test t4;
  t4.str = strdup("echo 1\\ 2 3"); t4.tokc = 3;
  t4.tokv = (char *[3]){"echo", "1\\ 2", "3"};

  esc_tokenize_test t5;
  t5.str = strdup("echo 1\\\\ 2 3"); t5.tokc = 4;
  t5.tokv = (char *[4]){"echo", "1\\\\", "2", "3"};

  esc_tokenize_test t6;
  t6.str = strdup(""); t6.tokc = 0;
  t6.tokv = (char *[0]){};

  esc_tokenize_test t7;
  t7.str = strdup(" \t           \t  \t"); t7.tokc = 0;
  t7.tokv = (char *[0]){};

  const int num_tests = 7;
  esc_tokenize_test tests[] = { t1, t2, t3, t4, t5, t6, t7 };
  for (int i = 0; i < num_tests; ++i) run_esc_tokenize_test(tests + i);
}

/*
 * IS_IN_STR UTILITY TESTS
 **/

typedef struct __is_in_str_test__ {
  char *str;
  char c;
  bool expected;
} is_in_str_test;

void run_is_in_str_test(is_in_str_test *tst) {
  assert(__is_in_str__(tst->str, tst->c) == tst->expected);
}

void test___is_in_str__() {
  is_in_str_test t;
  t.str = "";
  t.c = 'a';
  t.expected = false;
  run_is_in_str_test(&t);

  t.str = "abcdefghijklmnopqrstuvwqyzABCDEFGHIJLKMNOPQRSTUVWXYZ123456789!@#$%^&*()";
  int len = strlen(t.str);
  t.expected = true;
  for (int i = 0; i < len; ++i) { t.c = t.str[i]; run_is_in_str_test(&t); }
}

/*
 * CONCAT_STR UTILITY TESTS
 **/

void test___concat_str__() {
  assert(!strcmp(__concat_str__((char *[0]){}, 0, ""), ""));
  assert(!strcmp(__concat_str__((char *[0]){}, 0, " "), ""));
  assert(!strcmp(__concat_str__((char *[3]){"a", "b", "c"}, 3, ""), "abc"));
  assert(!strcmp(__concat_str__((char *[3]){"a", "b", "c"}, 3, " "), "a b c"));
}

/*
 * STRIP_STR UTILITY TESTS
 **/

void test___l_strip_str__() {
  assert(__r_strip_str__("", ws) == 0);
  assert(__l_strip_str__("1 2 3", ws) == 0);
  assert(__l_strip_str__("\t \t \t       \t", ws) == 12);
  assert(__l_strip_str__(" 1 2 3", ws) == 1);
  assert(__l_strip_str__("\t \t 1 3", ws) == 4);
}

void test___r_strip_str__() {
  assert(__r_strip_str__("", ws) == 0);
  assert(__r_strip_str__("1 2 3", ws) == 4);
  assert(__r_strip_str__("\t \t \t       \t", ws) == 0);
  assert(__r_strip_str__("1 2 3 ", ws) == 4);
  assert(__r_strip_str__("1 3 \t \t ", ws) == 2);
}

void test___strip_str__() {
  char *str;
  str = strdup("");
  assert(!strcmp(__strip_str__(str, ws), ""));      free(str);
  str = strdup("1 2 3");
  assert(!strcmp(__strip_str__(str, ws), "1 2 3")); free(str);
  str = strdup("\t \t \t       \t");
  assert(!strcmp(__strip_str__(str, ws), ""));      free(str);
  str = strdup("1 2 3 ");
  assert(!strcmp(__strip_str__(str, ws), "1 2 3")); free(str);
  str = strdup("1 3 \t \t ");
  assert(!strcmp(__strip_str__(str, ws), "1 3"));   free(str);
}

/*
 * IO_UTILITY TESTS ORCHESTRATOR
 **/

void test_io_utils() {
  test___l_strip_str__();
  test___r_strip_str__();
  test___strip_str__();
  test_esc_tokenize();
  test___is_in_str__();
  test___concat_str__();
}
