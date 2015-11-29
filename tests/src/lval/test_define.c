#include "test_define.h"

void test_lval_long(test *t) {
  lval* l = lval_long(233);

  test_assert(l->type == LVAL_LONG);
  test_assert(l->data.l == 233);

  lval_del(l);
}

void test_lval_double(test *t) {
  lval* d = lval_double(2.33);

  test_assert(d->type == LVAL_DOUBLE);
  test_assert(d->data.d == 2.33);

  lval_del(d);
}

void test_lval_sym(test *t) {
  lval* s = lval_sym("SYM");

  test_assert(s->type == LVAL_SYM);
  test_assert(strcmp(s->sym, "SYM") == 0);

  lval_del(s);
}

void test_lval_sexpr(test *t) {
  lval* s = lval_sexpr();

  test_assert(s->type == LVAL_SEXPR);
  test_assert(s->count == 0);
  test_assert(s->cell == NULL);

  lval_del(s);
}

void test_lval_qexpr(test *t) {
  lval* q = lval_qexpr();

  test_assert(q->type == LVAL_QEXPR);
  test_assert(q->count == 0);
  test_assert(q->cell == NULL);

  lval_del(q);
}

void test_lval_err(test *t) {
  lval* e = lval_err("ERR");

  test_assert(e->type == LVAL_ERR);
  test_assert(strcmp(e->err, "ERR") == 0);

  lval_del(e);
}
