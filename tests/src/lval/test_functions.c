#include "test_functions.h"

void test_head(test *t) {
  lval* a = lval_qexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_head(a);
  test_assert(h->type == LVAL_LONG);
  test_assert(h->data.l == 1);

  lval_del(h);
}

void test_head_with_too_many_args(test *t) {
}
void test_head_with_wrong_type(test *t) {
}
void test_head_with_empty_list(test *t) {
}

void test_list(test *t) {
}

void test_tail(test *t) {
}
void test_join(test *t) {
}
void test_eval(test *t) {
}
