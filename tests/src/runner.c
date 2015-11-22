#include "runner.h"

static int test_any() {
  test_assert(1 == 1);
  return 0;
}

static int test_some() {
  test_assert(1 == 2);
  return 0;
}


int run_all_tests() {
  run_test(test_any);
  run_test(test_some);
  return 0;
}

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;
int main(int arc, char** argv) {
  PRINT_RUN_START();
  run_all_tests();
  PRINT_RUN_RESULT();

  return tests_failed == 0;
}
