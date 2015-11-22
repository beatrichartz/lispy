#include <stdio.h>
#include "runner.h"

static int test_any() {
  test_assert(1 == 1);
  return 0;
}

static int test_some() {
  test_assert(1 == 2);
  return 0;
}

int all_tests() {
  run_test(test_any);
  run_test(test_some);
  return 0;
}

int tests_run = 0;
int main(int arc, char** argv) {
  int result = all_tests();
  if (result == 0) {
    printf("PASSED\n");
  }

  printf("Tests run: %d\n", tests_run);
}
