#ifndef RUNNER_TEST
#define RUNNER_TEST

#include <stdlib.h>
#include <strings.h>

enum outcome {
  TEST_PENDING,
  TEST_PASSED,
  TEST_FAILED,
} outcome;

typedef struct test test;
typedef void (*testfunc)(test *t);

struct test {
  testfunc func;
  enum outcome outcome;
  char *func_name;
  char *file_name;
  int line_number;
  char *failure_message;
  char *pending_message;
};

test* new_test(testfunc func, const char* func_name);
void destroy_test(test *t);

#endif
