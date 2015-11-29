#include "test_eval.h"

void test_lval_eval_simple(test *t) {
  lval* s = lval_sexpr();
  lval_add(s, lval_sym("+"));
  lval_add(s, lval_double(2.2));
  lval_add(s, lval_double(4.4));

  lval* result = lval_eval(s);

  test_assert(result->type == LVAL_DOUBLE);
  test_assert(result->data.d >= 6.59999999);
  test_assert(result->data.d <= 6.60000001);

  lval_del(result);
}

void test_lval_eval_nested(test *t) {
  lval* s = lval_sexpr();
  lval_add(s, lval_sym("/"));
  lval_add(s, lval_long(48));
  lval_add(s, lval_long(4));

  lval* n = lval_sexpr();
  lval_add(s, n);
  lval_add(n, lval_sym("-"));
  lval_add(n, lval_long(5));
  lval_add(n, lval_long(2));

  lval* result = lval_eval(s);

  test_assert(result->type == LVAL_LONG);
  test_assert(result->data.l == 4);

  lval_del(result);
}

void test_lval_eval_error(test *t) {
  lval* s = lval_sexpr();
  lval_add(s, lval_long(48));
  lval_add(s, lval_sym("/"));
  lval_add(s, lval_long(4));

  lval* result = lval_eval(s);

  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "S-expression does not start with a symbol") == 0);

  lval_del(result);
}

void test_lval_eval_nested_error(test *t) {
  lval* s = lval_sexpr();
  lval_add(s, lval_sym("/"));
  lval_add(s, lval_long(48));
  lval_add(s, lval_long(4));

  lval* n = lval_sexpr();
  lval_add(s, n);
  lval_add(n, lval_long(5));
  lval_add(n, lval_long(2));
  lval_add(n, lval_sym("-"));

  lval* result = lval_eval(s);

  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "S-expression does not start with a symbol") == 0);

  lval_del(result);
}

