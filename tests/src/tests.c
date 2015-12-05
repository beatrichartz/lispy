#include "suite.h"
#include "test_lval.h"
#include "test_parser.h"

void add_tests(suite *s) {
  add_test(s, test_lval_add);
  add_test(s, test_lval_pop);
  add_test(s, test_lval_take);

  add_test(s, test_lval_long);
  add_test(s, test_lval_double);
  add_test(s, test_lval_sym);
  add_test(s, test_lval_sexpr);
  add_test(s, test_lval_qexpr);
  add_test(s, test_lval_err);


  add_test(s, test_lval_eval_simple);
  add_test(s, test_lval_eval_nested);
  add_test(s, test_lval_eval_error);
  add_test(s, test_lval_eval_nested_error);
  add_test(s, test_lval_eval_operations);
  add_test(s, test_lval_eval_list_functions);
  add_test(s, test_lval_eval_list_function_join);
  add_test(s, test_lval_eval_list_function_eval);
  add_test(s, test_lval_eval_list_function_list);

  add_test(s, test_lval_double_addition);
  add_test(s, test_lval_double_subtraction);
  add_test(s, test_lval_double_multiplication);
  add_test(s, test_lval_double_division);

  add_test(s, test_lval_double_modulo);
  add_test(s, test_lval_double_power);

  add_test(s, test_lval_double_max);
  add_test(s, test_lval_double_min);

  add_test(s, test_lval_double_unary_minus);
  add_test(s, test_lval_unsupported_double);
  add_test(s, test_lval_unsupported_double_unary);


  add_test(s, test_lval_long_addition);
  add_test(s, test_lval_long_subtraction);
  add_test(s, test_lval_long_multiplication);
  add_test(s, test_lval_long_division);

  add_test(s, test_lval_long_modulo);
  add_test(s, test_lval_long_power);

  add_test(s, test_lval_long_max);
  add_test(s, test_lval_long_min);

  add_test(s, test_lval_long_unary_minus);
  add_test(s, test_lval_unsupported_long);
  add_test(s, test_lval_unsupported_long_unary);


  add_test(s, test_lval_print_sexpr);
  add_test(s, test_lval_print_qexpr);
  add_test(s, test_lval_print_double);
  add_test(s, test_lval_print_long);

  add_test(s, test_lval_read_sexpr);
  add_test(s, test_lval_read_sub_sexpr);
  add_test(s, test_lval_read_qexpr);
  add_test(s, test_lval_read_sub_qexpr);
  add_test(s, test_lval_read_double);
  add_test(s, test_lval_read_long);

  add_test(s, test_grammar_for_long);
  add_test(s, test_grammar_for_double);
  add_test(s, test_grammar_for_symbol);
  add_test(s, test_grammar_for_sexpr);
  add_test(s, test_grammar_for_qexpr);
  add_test(s, test_grammar_for_expr);
  add_test(s, test_grammar_for_lispy);


  add_test(s, test_list);
  add_test(s, test_head);
  add_test(s, test_head_with_too_many_args);
  add_test(s, test_head_with_wrong_type);
  add_test(s, test_head_with_empty_list);
  add_test(s, test_tail);
  add_test(s, test_tail_with_too_many_args);
  add_test(s, test_tail_with_wrong_type);
  add_test(s, test_tail_with_empty_list);
  add_test(s, test_join);
  add_test(s, test_join_with_wrong_type);
  add_test(s, test_eval);
  add_test(s, test_eval_with_too_many_args);
  add_test(s, test_eval_with_wrong_type);
}

