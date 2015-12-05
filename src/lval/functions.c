#include "functions.h"

lval* builtin_head(lval* v) {
  LISPY_ASSERT(v,
      v->count == 1,
      "Function 'head' passed too many arguments");

  LISPY_ASSERT(v,
      v->cell[0]->type == LVAL_QEXPR,
      "Function 'head' passed an incorrect type");

  LISPY_ASSERT(v,
      v->cell[0]->count > 0,
      "Function 'head' passed an empty list");

  lval *q = lval_take(v, 0);


  for(int i = 1; i < q->count; i++) {
    lval_del(q->cell[i]);
  }

  q->cell = realloc(q->cell, sizeof(lval*));
  q->count = 1;

  return q;
}

lval* builtin_cons(lval* v) {
  LISPY_ASSERT(v,
      v->count > 1,
      "Function 'cons' passed too few arguments");

  LISPY_ASSERT(v,
      v->count < 3,
      "Function 'cons' passed too many arguments");

  LISPY_ASSERT(v,
      v->cell[1]->type == LVAL_QEXPR,
      "Function 'cons' passed incorrect types");

  lval *list = lval_pop(v, 1);
  lval *val = lval_take(v, 0);

  list->count++;
  list->cell = realloc(list->cell, sizeof(lval*) * list->count);

  memmove(
      &list->cell[1],
      &list->cell[0],
      sizeof(lval*) * (list->count - 1)
  );

  list->cell[0] = val;

  return list;
}

lval* builtin_tail(lval* v) {
  LISPY_ASSERT(v,
      v->count == 1,
      "Function 'tail' passed too many arguments");

  LISPY_ASSERT(v,
      v->cell[0]->type == LVAL_QEXPR,
      "Function 'tail' passed an incorrect type");

  LISPY_ASSERT(v,
      v->cell[0]->count > 0,
      "Function 'tail' passed an empty list");

  lval *q = lval_take(v, 0);
  lval_del(lval_pop(q, 0));

  return q;
}

lval* builtin_list(lval* v) {
  v->type = LVAL_QEXPR;
  return v;
}

lval* builtin_eval(lval* v) {
  LISPY_ASSERT(v,
      v->count == 1,
      "Function 'eval' passed too many arguments");

  LISPY_ASSERT(v,
      v->cell[0]->type == LVAL_QEXPR,
      "Function 'eval' passed an incorrect type");

  lval *q = lval_take(v, 0);
  q->type = LVAL_SEXPR;

  return lval_eval(q);
}

lval* lval_join(lval *a, lval *b);
lval* builtin_join(lval* v) {
  for (int i = 0; i < v->count; i++) {
    LISPY_ASSERT(v,
        v->cell[i]->type == LVAL_QEXPR,
        "Function 'join' passed an incorrect type");
  }

  lval *q = lval_pop(v, 0);

  while (v->count) {
    q = lval_join(q, lval_pop(v, 0));
  }

  lval_del(v);
  return q;
}

lval* lval_join(lval *a, lval *b) {
  a->count = a->count + b->count;
  a->cell = realloc(a->cell, sizeof(lval*) * a->count);
  memmove(
      &a->cell[a->count - b->count],
      &b->cell[0],
      sizeof(lval*) * b->count
  );

  b->count = 0;
  lval_del(b);

  return a;
}

lval* builtin_len(lval* v) {
  LISPY_ASSERT(v,
      v->count == 1,
      "Function 'len' passed too many arguments");

  LISPY_ASSERT(v,
      v->cell[0]->type == LVAL_QEXPR,
      "Function 'len' passed an incorrect type");

  lval *q = lval_take(v, 0);
  lval *c = lval_long(q->count);
  lval_del(q);

  return c;
}
