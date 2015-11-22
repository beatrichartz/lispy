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

void lval_del(lval* v) {
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
      for (int i = 0; i < v->count; i++) {
        lval_del(v->cell[i]);
      }
      free(v->cell);
      break;
  }

  free(v);
}

