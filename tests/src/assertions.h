#ifndef LISPY_TEST_ASSERTIONS
#define LISPY_TEST_ASSERTIONS

#include <stdio.h>
#include <strings.h>
#include "colors.h"

#define PASS_ASSERTION(assertion) do {                                  \
  printf("%s%-30s%-40spassed%s\n",                                      \
         KGRN, __func__, assertion, RESET);                             \
} while(0)

#define FAIL_ASSERTION(assertion) do {                                  \
  printf("%s%-30s%-40sfailed%s\n",                                      \
         KRED, __func__, assertion, RESET);                             \
} while(0)

#define test_assert(assertion) do {                                     \
  if (assertion) {                                                      \
    PASS_ASSERTION(#assertion);                                         \
  } else {                                                              \
    FAIL_ASSERTION(#assertion);                                         \
    return assertion;                                                   \
  }                                                                     \
                                                                        \
} while(0)

#endif
