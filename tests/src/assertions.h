#ifndef LISPY_TEST_ASSERTIONS
#define LISPY_TEST_ASSERTIONS

#include <stdio.h>
#include <strings.h>
#include "colors.h"
#include "test.h"

int execute_test_assertion(
    test *t,
    int assertion,
    const char* assertion_string,
    const char* file_name,
    int line_number
);

void execute_mark_as_pending(
    test *t,
    const char* message,
    const char* file_name,
    int line_number
);

void pass_assertion(test *t, const char* assertion_string);
void fail_assertion(test *t, const char* assertion_string);

#define test_assert(assertion) do {                \
  int _assertion_result_ = execute_test_assertion( \
      t,                                           \
      assertion,                                   \
      #assertion,                                  \
      __FILE__,                                    \
      __LINE__                                     \
  );                                               \
                                                   \
  if (!_assertion_result_) {                       \
    return;                                        \
  }                                                \
} while(0)

#define pending(message) do {                      \
  execute_mark_as_pending(                         \
      t,                                           \
      message,                                     \
      __FILE__,                                    \
      __LINE__                                     \
  );                                               \
                                                   \
  return;                                          \
} while(0)

#endif
