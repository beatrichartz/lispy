#include "test_operations.h"

void test_lval_add(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);

  test_assert(a->count == 1);
  test_assert(a->cell[0] == b);

  lval_del(a);
}

void test_lval_pop(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);
  lval_pop(a, 0);

  test_assert(a->count == 0);
  test_assert(a->cell == NULL);

  lval_del(a);
  lval_del(b);
}

void test_lval_take(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);
  lval *y = lval_take(a, 0);

  test_assert(y == b);

  lval_del(b);
}

