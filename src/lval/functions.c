#include "functions.h"

lval* builtin_head(lval* v) {
  lval *q = lval_take(v, 0);

  while(q->count > 1) { lval_del(lval_pop(q, 1)); }
  return q;
}
