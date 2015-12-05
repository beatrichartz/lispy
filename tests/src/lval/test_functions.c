#include "test_functions.h"

void test_head(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();

  lval_add(x, a);
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_head(x);
  test_assert(h->type == LVAL_QEXPR);
  test_assert(h->count == 1);
  test_assert(h->cell[0]->type == LVAL_LONG);
  test_assert(h->cell[0]->data.l == 1);

  lval_del(h);
}

void test_head_with_too_many_args(test *t) {
  lval* a = lval_qexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_head(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'head' passed too many arguments") == 0);

  lval_del(h);
}
void test_head_with_wrong_type(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_long(1);

  lval_add(a, b);

  lval *h = builtin_head(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'head' passed an incorrect type") == 0);

  lval_del(h);
}
void test_head_with_empty_list(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();

  lval_add(x, a);

  lval *h = builtin_head(x);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'head' passed an empty list") == 0);

  lval_del(h);
}

void test_cons(test *t) {
  lval* x = lval_sexpr();
  lval_add(x, lval_long(1));

  lval* a = lval_qexpr();
  lval_add(x, a);

  lval* b = lval_long(2);
  lval* c = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);

  lval *h = builtin_cons(x);
  test_assert(h->type == LVAL_QEXPR);
  test_assert(h->count == 3);
  test_assert(h->cell[0]->type == LVAL_LONG);
  test_assert(h->cell[0]->data.l == 1);
  test_assert(h->cell[1]->type == LVAL_LONG);
  test_assert(h->cell[1]->data.l == 2);
  test_assert(h->cell[2]->type == LVAL_LONG);
  test_assert(h->cell[2]->data.l == 3);

  lval_del(h);
}

void test_cons_with_too_few_args(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();
  lval_add(x, a);

  lval* b = lval_long(2);
  lval* c = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);

  lval *h = builtin_cons(x);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'cons' passed too few arguments") == 0);

  lval_del(h);
}

void test_cons_with_too_many_args(test *t) {
  lval* x = lval_sexpr();
  lval_add(x, lval_long(1));
  lval_add(x, lval_long(1));

  lval* a = lval_qexpr();
  lval_add(x, a);

  lval* b = lval_long(2);
  lval* c = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);

  lval *h = builtin_cons(x);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'cons' passed too many arguments") == 0);

  lval_del(h);
}

void test_cons_with_wrong_type(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(1);

  lval_add(a, b);
  lval_add(a, c);

  lval *h = builtin_cons(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'cons' passed incorrect types") == 0);

  lval_del(h);
}

void test_tail(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();

  lval_add(x, a);
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_tail(x);
  test_assert(h->type == LVAL_QEXPR);
  test_assert(h->count == 2);
  test_assert(h->cell[0]->type == LVAL_LONG);
  test_assert(h->cell[0]->data.l == 2);
  test_assert(h->cell[1]->type == LVAL_LONG);
  test_assert(h->cell[1]->data.l == 3);

  lval_del(h);
}

void test_tail_with_too_many_args(test *t) {
  lval* a = lval_qexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_tail(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'tail' passed too many arguments") == 0);

  lval_del(h);
}
void test_tail_with_wrong_type(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_long(1);

  lval_add(a, b);

  lval *h = builtin_tail(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'tail' passed an incorrect type") == 0);

  lval_del(h);
}
void test_tail_with_empty_list(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();

  lval_add(x, a);

  lval *h = builtin_tail(x);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'tail' passed an empty list") == 0);

  lval_del(h);
}

void test_list(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_list(a);
  test_assert(h->type == LVAL_QEXPR);
  test_assert(h->count == 3);
  test_assert(h->cell[0]->data.l == 1);
  test_assert(h->cell[1]->data.l == 2);
  test_assert(h->cell[2]->data.l == 3);

  lval_del(h);
}

void test_eval(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();

  lval_add(x, a);
  lval* b = lval_sym("+");
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_eval(x);
  test_assert(h->type == LVAL_LONG);
  test_assert(h->data.l == 5);

  lval_del(h);
}

void test_eval_with_too_many_args(test *t) {
  lval* a = lval_qexpr();
  lval* b = lval_long(1);
  lval* c = lval_long(2);
  lval* d = lval_long(3);

  lval_add(a, b);
  lval_add(a, c);
  lval_add(a, d);

  lval *h = builtin_eval(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'eval' passed too many arguments") == 0);

  lval_del(h);
}

void test_eval_with_wrong_type(test *t) {
  lval* a = lval_sexpr();
  lval* b = lval_long(1);

  lval_add(a, b);

  lval *h = builtin_eval(a);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'eval' passed an incorrect type") == 0);

  lval_del(h);
}

void test_join(test *t) {
  lval* a = lval_qexpr();
  lval* q = lval_long(1);
  lval* r = lval_long(2);
  lval* s = lval_long(3);

  lval_add(a, q);
  lval_add(a, r);
  lval_add(a, s);

  lval* b = lval_qexpr();
  lval* x = lval_long(4);
  lval* y = lval_long(5);

  lval_add(b, x);
  lval_add(b, y);

  lval* c = lval_sexpr();
  lval_add(c, a);
  lval_add(c, b);

  lval *h = builtin_join(c);
  test_assert(h->type == LVAL_QEXPR);
  test_assert(h->count == 5);
  test_assert(h->cell[0]->data.l == 1);
  test_assert(h->cell[1]->data.l == 2);
  test_assert(h->cell[2]->data.l == 3);
  test_assert(h->cell[3]->data.l == 4);
  test_assert(h->cell[4]->data.l == 5);

  lval_del(h);
}

void test_join_with_wrong_type(test *t) {
  lval* a = lval_qexpr();
  lval* q = lval_long(1);
  lval* r = lval_long(2);
  lval* s = lval_long(3);

  lval_add(a, q);
  lval_add(a, r);
  lval_add(a, s);

  lval* b = lval_long(4);

  lval* c = lval_sexpr();
  lval_add(c, a);
  lval_add(c, b);

  lval *h = builtin_join(c);
  test_assert(h->type == LVAL_ERR);
  test_assert(strcmp(h->err, "Function 'join' passed an incorrect type") == 0);

  lval_del(h);
}

void test_len(test *t) {
  lval* x = lval_sexpr();
  lval* a = lval_qexpr();
  lval_add(x, a);

  lval* q = lval_long(4);
  lval* r = lval_long(8);
  lval* s = lval_long(9);

  lval_add(a, q);
  lval_add(a, r);
  lval_add(a, s);

  lval *h = builtin_len(x);
  test_assert(h->type == LVAL_LONG);
  test_assert(h->data.l == 3);

  lval_del(h);
}
