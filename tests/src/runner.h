#ifndef LISPY_TEST_RUNNER
#define LISPY_TEST_RUNNER

#include <stdio.h>
#include "colors.h"
#include "assertions.h"
#include "lispy.h"

#define PRINT_RUN_START()                                              \
  printf("\n%s**************************************** RUNNING TESTS *****************************************%s\n\n", KCYN, RESET);

#define PRINT_RUN_RESULT() do {                                        \
  char* color = (tests_failed == 0) ? KGRN : KRED;                     \
  char* message = "%s***************************** %3.1d TEST RUN, %3.1d PASSED, %3.1d FAILED *****************************%s\n"; \
  printf(message, color, tests_run, tests_passed, tests_failed, RESET);\
} while(0)

#define PASS(test) do {                                                \
  tests_passed++;                                                      \
  printf("\n");                                                        \
} while(0)

#define FAIL(test) do {                                                \
  tests_failed++;                                                      \
  printf("\n");                                                        \
} while(0)

#define run_test(test) do {                                            \
  int r = test();                                                      \
  tests_run++;                                                         \
                                                                       \
  if (r) {                                                             \
    PASS(test);                                                        \
  } else {                                                             \
    FAIL(test);                                                        \
  }                                                                    \
} while(0)

extern int tests_run;
extern int tests_passed;
extern int tests_failed;

#endif
