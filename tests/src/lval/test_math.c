#include "test_math.h"

void test_lval_double_addition(test *t) {
  lval* e = sexpr_double_mock(2, 3.0, 3.0);
  lval* result = builtin_op(e, "+");
  test_assert(result->data.d == 6.0);

  lval_del(result);

  e = sexpr_double_mock(2, 3.0, 3.0);
  result = builtin_op(e, "add");
  test_assert(result->data.d == 6.0);

  lval_del(result);
}
void test_lval_double_subtraction(test *t) {
  lval* e = sexpr_double_mock(2, 5.0, 3.0);
  lval* result = builtin_op(e, "-");
  test_assert(result->data.d == 2.0);

  lval_del(result);

  e = sexpr_double_mock(2, 5.0, 3.0);
  result = builtin_op(e, "sub");
  test_assert(result->data.d == 2.0);

  lval_del(result);
}
void test_lval_double_multiplication(test *t) {
  lval* e = sexpr_double_mock(2, 5.0, 3.0);
  lval* result = builtin_op(e, "*");
  test_assert(result->data.d == 15.0);

  lval_del(result);

  e = sexpr_double_mock(2, 5.0, 3.0);
  result = builtin_op(e, "mul");
  test_assert(result->data.d == 15.0);

  lval_del(result);
}
void test_lval_double_division(test *t) {
  lval* e = sexpr_double_mock(2, 6.0, 3.0);
  lval* result = builtin_op(e, "/");
  test_assert(result->data.d == 2.0);

  lval_del(result);

  e = sexpr_double_mock(2, 6.0, 3.0);
  result = builtin_op(e, "div");
  test_assert(result->data.d == 2.0);

  lval_del(result);
}

void test_lval_double_modulo(test *t) {
  lval* e = sexpr_double_mock(2, 6.0, 4.0);
  lval* result = builtin_op(e, "%");
  test_assert(result->data.d == 2.0);

  lval_del(result);

  e = sexpr_double_mock(2, 6.0, 4.0);
  result = builtin_op(e, "mod");
  test_assert(result->data.d == 2.0);

  lval_del(result);
}
void test_lval_double_power(test *t) {
  lval* e = sexpr_double_mock(2, 4.0, 2.0);
  lval* result = builtin_op(e, "^");
  test_assert(result->data.d == 16.0);

  lval_del(result);

  e = sexpr_double_mock(2, 4.0, 2.0);
  result = builtin_op(e, "pow");
  test_assert(result->data.d == 16.0);

  lval_del(result);
}

void test_lval_double_max(test *t) {
  lval* e = sexpr_double_mock(3, 4.0, 22.0, 1.0);
  lval* result = builtin_op(e, "max");
  test_assert(result->data.d == 22.0);

  lval_del(result);
}
void test_lval_double_min(test *t) {
  lval* e = sexpr_double_mock(5, 4.0, 22.0, -1.0, 0.5, 2.0);
  lval* result = builtin_op(e, "min");
  test_assert(result->data.d == -1.0);

  lval_del(result);
}

void test_lval_double_unary_minus(test *t) {
  lval* e = sexpr_double_mock(1, 4.0);
  lval* result = builtin_op(e, "-");
  test_assert(result->data.d == -4.0);

  lval_del(result);
}

void test_lval_unsupported_double(test *t) {
  lval* e = sexpr_double_mock(2, 4.0, 0.0);
  lval* result = builtin_op(e, "&");
  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "Unknown operation") == 0);

  lval_del(result);
}

void test_lval_unsupported_double_unary(test *t) {
  lval* e = sexpr_double_mock(1, 4.0);
  lval* result = builtin_op(e, "&");
  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "Unknown unary operation") == 0);

  lval_del(result);
}


void test_lval_long_addition(test *t) {
  lval* e = sexpr_long_mock(2, 3, 3);
  lval* result = builtin_op(e, "+");
  test_assert(result->data.l == 6);

  lval_del(result);

  e = sexpr_long_mock(2, 3, 3);
  result = builtin_op(e, "add");
  test_assert(result->data.l == 6);

  lval_del(result);
}
void test_lval_long_subtraction(test *t) {
  lval* e = sexpr_long_mock(2, 5, 3);
  lval* result = builtin_op(e, "-");
  test_assert(result->data.l == 2);

  lval_del(result);

  e = sexpr_long_mock(2, 5, 3);
  result = builtin_op(e, "sub");
  test_assert(result->data.l == 2);

  lval_del(result);
}
void test_lval_long_multiplication(test *t) {
  lval* e = sexpr_long_mock(2, 5, 3);
  lval* result = builtin_op(e, "*");
  test_assert(result->data.l == 15);

  lval_del(result);

  e = sexpr_long_mock(2, 5, 3);
  result = builtin_op(e, "mul");
  test_assert(result->data.l == 15);

  lval_del(result);
}
void test_lval_long_division(test *t) {
  lval* e = sexpr_long_mock(2, 6, 3);
  lval* result = builtin_op(e, "/");
  test_assert(result->data.l == 2);

  lval_del(result);

  e = sexpr_long_mock(2, 6, 3);
  result = builtin_op(e, "div");
  test_assert(result->data.l == 2);

  lval_del(result);
}

void test_lval_long_modulo(test *t) {
  lval* e = sexpr_long_mock(2, 6, 4);
  lval* result = builtin_op(e, "%");
  test_assert(result->data.l == 2);

  lval_del(result);

  e = sexpr_long_mock(2, 6, 4);
  result = builtin_op(e, "mod");
  test_assert(result->data.l == 2);

  lval_del(result);
}
void test_lval_long_power(test *t) {
  lval* e = sexpr_long_mock(2, 4, 2);
  lval* result = builtin_op(e, "^");
  test_assert(result->data.l == 16);

  lval_del(result);

  e = sexpr_long_mock(2, 4, 2);
  result = builtin_op(e, "pow");
  test_assert(result->data.l == 16);

  lval_del(result);
}

void test_lval_long_max(test *t) {
  lval* e = sexpr_long_mock(3, 4, 22, 1);
  lval* result = builtin_op(e, "max");
  test_assert(result->data.l == 22);

  lval_del(result);
}
void test_lval_long_min(test *t) {
  long x = -2;
  lval* e = sexpr_long_mock(5, 4, 22, 1, x, 2);
  lval* result = builtin_op(e, "min");
  test_assert(result->data.l == -2);

  lval_del(result);
}

void test_lval_long_unary_minus(test *t) {
  lval* e = sexpr_long_mock(1, 4);
  lval* result = builtin_op(e, "-");
  test_assert(result->data.l == -4);

  lval_del(result);
}

void test_lval_unsupported_long(test *t) {
  lval* e = sexpr_long_mock(2, 4, 2);
  lval* result = builtin_op(e, "&");

  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "Unknown operation") == 0);

  lval_del(result);
}

void test_lval_unsupported_long_unary(test *t) {
  lval* e = sexpr_long_mock(1, 4);
  lval* result = builtin_op(e, "&");

  test_assert(result->type == LVAL_ERR);
  test_assert(strcmp(result->err, "Unknown unary operation") == 0);

  lval_del(result);
}
