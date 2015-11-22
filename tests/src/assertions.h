#ifndef LISPY_TEST_ASSERTIONS
#define LISPY_TEST_ASSERTIONS

#include <stdio.h>
#include <strings.h>
#include "colors.h"

#define PASS_ASSERTION(assertion) do {                                 \
  printf("%s%s:\t%s%s\n",                                                  \
         KGRN, __func__, assertion, RESET);                                      \
} while(0)

#define FAIL_ASSERTION(assertion) do {                                 \
  printf("%s%s:\t%s%s\n",                                                \
         KRED, __func__, assertion, RESET);                                      \
} while(0)

#define test_assert(assertion) do {                                    \
  if (assertion) {                                                     \
    PASS_ASSERTION("" #assertion "\tpassed");                          \
  } else {                                                             \
    FAIL_ASSERTION("" #assertion "\tfailed");                          \
    return assertion;                                                  \
  }                                                                    \
                                                                       \
} while(0)

#endif
