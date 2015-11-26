#include "test_define.h"

int test_lval_long() {
  lval* l = lval_long(233);

  test_assert(l->type == LVAL_LONG);
  test_assert(l->data.l == 233);

  lval_del(l);

  return 1;
}

int test_lval_double() {
  lval* d = lval_double(2.33);

  test_assert(d->type == LVAL_DOUBLE);
  test_assert(d->data.d == 2.33);

  lval_del(d);

  return 1;
}

int test_lval_sym() {
  lval* s = lval_sym("SYM");

  test_assert(s->type == LVAL_SYM);
  test_assert(strcmp(s->sym, "SYM") == 0);

  lval_del(s);

  return 1;
}

int test_lval_sexpr() {
  lval* s = lval_sexpr();

  test_assert(s->type == LVAL_SEXPR);
  test_assert(s->count == 0);
  test_assert(s->cell == NULL);

  lval_del(s);

  return 1;
}

int test_lval_err() {
  lval* e = lval_err("ERR");

  test_assert(e->type == LVAL_ERR);
  test_assert(strcmp(e->err, "ERR") == 0);

  lval_del(e);

  return 1;
}
