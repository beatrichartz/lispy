#include "runner.h"
#include "test_lval.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

int run_all_tests() {
  run_test(test_lval_add);
  run_test(test_lval_pop);
  run_test(test_lval_take);
  return 0;
}

int main(int arc, char** argv) {
  PRINT_RUN_START();
  run_all_tests();
  PRINT_RUN_RESULT();

  return tests_failed == 1;
}
