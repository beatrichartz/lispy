#include "define.h"

lval* lval_long(long num) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_LONG;
  v->data.l = num;
  return v;
}

lval* lval_double(double num) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_DOUBLE;
  v->data.d = num;
  return v;
}

lval* lval_sym(char* s) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SYM;
  v->sym = malloc(strlen(s) + 1);
  strcpy(v->sym, s);
  return v;
}

lval* lval_sexpr(void) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

lval* lval_err(char* m) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_ERR;
  v->err = malloc(strlen(m) + 1);
  strcpy(v->err, m);

  return v;
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

