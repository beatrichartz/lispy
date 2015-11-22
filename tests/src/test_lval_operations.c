#include "test_lval_operations.h"

int test_lval_add() {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);

  test_assert(a->count == 1);
  test_assert(a->cell[0] == b);

  lval_del(a);

  return 1;
}

int test_lval_pop() {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);
  lval_pop(a, 1);

  test_assert(a->count == 0);
  test_assert(a->cell == NULL);

  lval_del(a);

  return 1;
}

int test_lval_take() {
  lval* a = lval_sexpr();
  lval* b = lval_sexpr();

  lval_add(a, b);
  lval_take(a, 1);

  test_assert(a->count == 0);
  test_assert(a->cell == NULL);

  return 1;
}

