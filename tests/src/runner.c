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


  run_test(test_lval_double_addition);
  run_test(test_lval_double_subtraction);
  run_test(test_lval_double_multiplication);
  run_test(test_lval_double_division);

  run_test(test_lval_double_modulo);
  run_test(test_lval_double_power);

  run_test(test_lval_double_max);
  run_test(test_lval_double_min);

  run_test(test_lval_double_unary_minus);
  run_test(test_lval_unsupported_double);
  run_test(test_lval_unsupported_double_unary);


  run_test(test_lval_long_addition);
  run_test(test_lval_long_subtraction);
  run_test(test_lval_long_multiplication);
  run_test(test_lval_long_division);

  run_test(test_lval_long_modulo);
  run_test(test_lval_long_power);

  run_test(test_lval_long_max);
  run_test(test_lval_long_min);

  run_test(test_lval_long_unary_minus);
  run_test(test_lval_unsupported_long);
  run_test(test_lval_unsupported_long_unary);


  run_test(test_lval_print_sexpr);
  run_test(test_lval_print_double);
  run_test(test_lval_print_long);

  run_test(test_lval_read_sexpr);
  run_test(test_lval_read_sub_sexpr);
  run_test(test_lval_read_double);
  run_test(test_lval_read_long);

  return 0;
}

int main(int arc, char** argv) {
  PRINT_RUN_START();
  run_all_tests();
  PRINT_RUN_RESULT();

  return tests_failed == 1;
}
