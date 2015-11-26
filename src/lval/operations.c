#include "operations.h"
#include <stdio.h>

lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  v->cell[v->count-1] = x;

  return v;
}

lval* lval_pop(lval* v, int i) {
  lval* x = malloc(sizeof(lval));
  memcpy(x, v->cell[i], sizeof(lval));

  memmove(
      &v->cell[i],
      &v->cell[i+1],
      sizeof(lval*) * v->count - i - 1
  );

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

void free_cell(lval** cell, int count);
void lval_del(lval* v) {
  if (v == NULL) {
    return;
  }

  switch(v->type) {
    case LVAL_LONG:
      break;
    case LVAL_DOUBLE:
      break;
    case LVAL_ERR:
      free(v->err);
      break;
    case LVAL_SYM:
      free(v->sym);
      break;
    case LVAL_SEXPR:
      free_cell(v->cell, v->count);
      break;
  }

  free(v);
  v = NULL;
}

void free_cell(lval** cell, int count) {
  if (cell == NULL) {
    return;
  }
  for (int i = 0; i < count; i++) {
    lval_del(cell[i]);
  }

  free(cell);
  cell = NULL;
}
