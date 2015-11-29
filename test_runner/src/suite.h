#ifndef RUNNER_SUITE
#define RUNNER_SUITE

#include <stdio.h>
#include "test.h"

typedef struct {
  test **tests;
  size_t size;
  size_t capacity;
} suite;

suite* new_suite(size_t initial_capacity);
void execute_add_test_to_suite(suite *s, testfunc func, const char* func_name);
void destroy_suite(suite *s);
void destroy_test(test *t);
void destroy_string_field(char *s);
void randomize_suite(suite *s, int seed);
void add_tests(suite *s);

#define add_test(s, f) do {  \
  execute_add_test_to_suite( \
      s,                     \
      f,                     \
      #f                     \
  );                         \
} while(0);

#endif
