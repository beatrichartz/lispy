#include "suite.h"
#include "test_lval.h"
#include "test_parser.h"

suite* add_all_tests() {
  suite *s = new_suite(20);
  add_test(s, test_lval_add);
  add_test(s, test_lval_pop);
  add_test(s, test_lval_take);


  add_test(s, test_lval_long);
  add_test(s, test_lval_double);
  add_test(s, test_lval_sym);
  add_test(s, test_lval_sexpr);
  add_test(s, test_lval_err);


  add_test(s, test_lval_eval_simple);
  add_test(s, test_lval_eval_nested);
  add_test(s, test_lval_eval_error);
  add_test(s, test_lval_eval_nested_error);


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
  add_test(s, test_lval_print_double);
  add_test(s, test_lval_print_long);

  add_test(s, test_lval_read_sexpr);
  add_test(s, test_lval_read_sub_sexpr);
  add_test(s, test_lval_read_double);
  add_test(s, test_lval_read_long);

  add_test(s, test_grammar_for_long);
  add_test(s, test_grammar_for_double);
  add_test(s, test_grammar_for_symbol);
  add_test(s, test_grammar_for_sexpr);
  add_test(s, test_grammar_for_expr);
  add_test(s, test_grammar_for_lispy);

  return s;
}

suite* new_suite(size_t initial_capacity) {
  suite *s = malloc(sizeof(suite));;
  s->size = 0;
  s->capacity = initial_capacity;
  s->tests = (test**) malloc(initial_capacity * sizeof(test*));
  if (s->tests == NULL) {
    printf("Failed to allocate tests array\n");
    exit(1);
  }

  return s;
}

void execute_add_test_to_suite(suite *s, testfunc func, const char* func_name) {
  if (s->capacity == s->size) {
    s->capacity *= 2;
    s->tests = (test**) realloc(s->tests, s->capacity * sizeof(test*));
    if (s->tests == NULL) {
      printf("Failed to allocate tests array\n");
      exit(1);
    }
  }

  s->tests[s->size++] = new_test(func, func_name);
}

void destroy_suite(suite *s) {
  for (int i = 0; i < s->size; i++) {
    destroy_test(s->tests[i]);
  }
  free(s->tests);
  s->tests = NULL;
  s->capacity = 0;
  s->size = 0;
  free(s);
  s = NULL;
}

void randomize_suite(suite *s, int seed) {
    srand48(seed);

    for (int i = 0; i < s->size; i++) {
      size_t j = (unsigned int) (drand48()*(i+1));
      test *t = s->tests[j];
      s->tests[j] = s->tests[i];
      s->tests[i] = t;
    }
}

