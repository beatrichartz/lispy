#pragma once

#include <stdio.h>
#include "test.h"

typedef struct {
  test **tests;
  size_t size;
  size_t capacity;
  int focused_tests;
  int crossed_tests;
} suite;

suite* new_suite(size_t initial_capacity);
void execute_add_test_to_suite(suite *s, testfunc func, const char* func_name, int focused, int crossed);
void destroy_suite(suite *s);
void destroy_test(test *t);
void destroy_string_field(char *s);
void randomize_suite(suite *s, int seed);
void add_tests(suite *s);

#define add_test(s, f) do {  \
  execute_add_test_to_suite( \
      s,                     \
      f,                     \
      #f,                    \
      0,                     \
      0                      \
  );                         \
} while(0);

#define fadd_test(s, f) do { \
  execute_add_test_to_suite( \
      s,                     \
      f,                     \
      #f,                    \
      1,                     \
      0                      \
  );                         \
} while(0);

#define xadd_test(s, f) do { \
  execute_add_test_to_suite( \
      s,                     \
      f,                     \
      #f,                    \
      0,                     \
      1                      \
  );                         \
} while(0);
