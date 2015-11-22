#ifndef LISPY_TEST_ASSERTIONS
#define LISPY_TEST_ASSERTIONS

#include <stdio.h>
#include "colors.h"

#define PASS() do {                                                    \
  printf("%sPASSED: %s()%s\n", KGRN, __func__, RESET);                 \
} while(0)

#define FAIL() do {                                                    \
  printf("%sFAILED: %s()%s\n", KRED, __func__, RESET);                 \
} while(0)

#define test_assert(test) do {                                         \
  if (test) {                                                          \
    PASS();                                                            \
  } else {                                                             \
    FAIL();                                                            \
  }                                                                    \
                                                                       \
  return test;                                                         \
} while(0)

#endif
