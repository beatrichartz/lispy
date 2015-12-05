#include "eval.h"
char operations[19][5] = {
  "+", "-", "*", "/", "%", "^",
  "add", "sub", "mul", "div", "mod", "pow",
  "min", "max",
  "list", "head", "tail", "join", "eval"
};

lval* builtin(lval* v, char* func) {
  if (strcmp("head", func) == 0) { return builtin_head(v); }
  if (strcmp("tail", func) == 0) { return builtin_tail(v); }
  if (strcmp("join", func) == 0) { return builtin_join(v); }
  if (strcmp("eval", func) == 0) { return builtin_eval(v); }
  if (strcmp("list", func) == 0) { return builtin_list(v); }

  return builtin_op(v, func);
}

lval* lval_eval_sexpr(lval* v) {
  for (int i = 0; i < v->count; i++) {
    v->cell[i] = lval_eval(v->cell[i]);
  }

  for (int i = 0; i < v->count; i++) {
    if (v->cell[i]->type == LVAL_ERR) {
      lval *err = lval_err(v->cell[i]->err);
      lval_del(v);
      return err;
    }
  }

  if (v->count == 0) { return v; }
  if (v->count == 1) { return lval_take(v, 0); }

  lval* f = lval_pop(v, 0);
  if (f->type != LVAL_SYM) {
    lval_del(f); lval_del(v);

    return lval_err("S-expression does not start with a symbol");
  }

  lval* result = builtin(v, f->sym);
  lval_del(f);

  return result;
}

lval* lval_eval(lval* v) {
  if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }

  return v;
}
