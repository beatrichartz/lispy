#include "operations.h"

lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  v->cell[v->count-1] = x;

  return v;
}

lval* lval_pop(lval* v, int i) {
  lval* x = v->cell[i];

  memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*) * v->count - i - 1);

  v->count--;
  if (v->count == 0) {
    free(v->cell);
    v->cell = NULL;
  } else {
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  }

  return x;
}

lval* lval_take(lval* v, int i) {
  lval* x = lval_pop(v, i);
  lval_del(v);
  return x;
}
