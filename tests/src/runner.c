#include "runner.h"
#include "test_lval.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

int run_all_tests() {
  run_test(test_lval_add);
  run_test(test_lval_pop);
  run_test(test_lval_take);
  run_test(test_lval_long);
  run_test(test_lval_double);
  run_test(test_lval_sym);
  run_test(test_lval_sexpr);
  run_test(test_lval_err);
  run_test(test_lval_eval_simple);
  run_test(test_lval_eval_nested);
  run_test(test_lval_eval_error);
  run_test(test_lval_eval_nested_error);
  return 0;
}

int main(int arc, char** argv) {
  PRINT_RUN_START();
  run_all_tests();
  PRINT_RUN_RESULT();

  return tests_failed == 1;
}
