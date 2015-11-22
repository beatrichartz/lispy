#include "lang.h"

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

void print_lval_expr(lval* v, char open, char close) {
  putchar(open);
  for (int i = 0; i < v->count; i++) {
    print_lval(v->cell[i]);

    if (i != (v->count-1)) {
      putchar(' ');
    }
  }
  putchar(close);
}

void print_lval(lval* v) {
  switch (v->type) {
    case LVAL_LONG:
      printf("%li", v->data.l);
      break;

    case LVAL_DOUBLE:
      printf("%f", v->data.d);
      break;

    case LVAL_SYM:
      printf("%s", v->sym);
      break;

    case LVAL_SEXPR:
      print_lval_expr(v, '(', ')');
      break;

    case LVAL_ERR:
      printf("Error: %s", v->err);
      break;

    default:
      printf("Unknown lval type: %d\n", v->type);
      break;
  }
}

void println_lval(lval* v) {
  print_lval(v);
  putchar('\n');
}

lval* builtin_op_long(lval* x, char* op, lval* y) {
  if (strcmp(op, "+") == 0)   { x->data.l += y->data.l; return x; }
  if (strcmp(op, "add") == 0) { x->data.l += y->data.l; return x; }

  if (strcmp(op, "-") == 0)   { x->data.l -= y->data.l; return x; }
  if (strcmp(op, "sub") == 0) { x->data.l -= y->data.l; return x; }

  if (strcmp(op, "*") == 0)   { x->data.l *= y->data.l; return x; }
  if (strcmp(op, "mul") == 0) { x->data.l *= y->data.l; return x; }

  int is_div = (strcmp(op, "/") == 0 || strcmp(op, "div") == 0.0);
  if (is_div && y->data.l == 0)   { return lval_err("division by zero"); }
  else if (is_div)            { x->data.l /= y->data.l; return x; }

  if (strcmp(op, "%") == 0)   { x->data.l %= y->data.l; return x; }
  if (strcmp(op, "mod") == 0) { x->data.l %= y->data.l; return x; }

  if (strcmp(op, "^") == 0)   { x->data.l ^= y->data.l; return x; }
  if (strcmp(op, "pow") == 0) { x->data.l ^= y->data.l; return x; }

  int is_max = (strcmp(op, "max") == 0);
  if (is_max && x->data.l < y->data.l) { x->data.l = y->data.l; return x; }
  else if (is_max) { return x; }

  int is_min = (strcmp(op, "min") == 0);
  if (is_min && x->data.l > y->data.l) { x->data.l = y->data.l; return x; }
  else if (is_min) { return x; }

  return lval_err("bad operation");
}

lval* builtin_op_double(lval* x, char* op, lval* y) {
  if (strcmp(op, "+") == 0)   { x->data.d += y->data.d; return x; }
  if (strcmp(op, "add") == 0) { x->data.d += y->data.d; return x; }

  if (strcmp(op, "-") == 0)   { x->data.d -= y->data.d; return x; }
  if (strcmp(op, "sub") == 0) { x->data.d -= y->data.d; return x; }

  if (strcmp(op, "*") == 0)   { x->data.d *= y->data.d; return x; }
  if (strcmp(op, "mul") == 0) { x->data.d *= y->data.d; return x; }

  int is_div = (strcmp(op, "/") == 0 || strcmp(op, "div") == 0.0);
  if (is_div && y->data.d == 0)   { return lval_err("division by zero"); }
  else if (is_div)            { x->data.d /= y->data.d; return x; }

  if (strcmp(op, "%") == 0)   { x->data.d = fmod(x->data.d, y->data.d); return x; }
  if (strcmp(op, "mod") == 0) { x->data.d = fmod(x->data.d, y->data.d); return x; }

  if (strcmp(op, "^") == 0)   { x->data.d = pow(x->data.d, y->data.d); return x; }
  if (strcmp(op, "pow") == 0) { x->data.d = pow(x->data.d, y->data.d); return x; }

  int is_max = (strcmp(op, "max") == 0);
  if (is_max && x->data.d < y->data.d) { x->data.d = y->data.d; return x; }
  else if (is_max) { return x; }

  int is_min = (strcmp(op, "min") == 0);
  if (is_min && x->data.d > y->data.d) { x->data.d = y->data.d; return x; }
  else if (is_min) { return x; }

  return lval_err("bad operation");
}

lval* lval_read_long(mpc_ast_t* t) {
  errno = 0;
  long x = strtol(t->contents, NULL, 10);

  if (errno == ERANGE) {
    return lval_err("invalid integer");
  } else {
    return lval_long(x);
  }
}

lval* lval_read_double(mpc_ast_t* t) {
  errno = 0;
  double x = strtof(t->contents, NULL);

  if (errno == ERANGE) {
    return lval_err("invalid double");
  } else {
    return lval_double(x);
  }
}

lval* lval_read(mpc_ast_t* t) {
  if (strstr(t->tag, "long"))   { return lval_read_long(t); }
  if (strstr(t->tag, "double")) { return lval_read_double(t); }
  if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

  lval* x = NULL;
  if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
  if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }

  for (int i = 0; i < t->children_num; i++) {
    mpc_ast_t* child = t->children[i];
    char* contents = child->contents;
    if (strcmp(contents, "(") == 0) { continue; }
    if (strcmp(contents, ")") == 0) { continue; }
    if (strcmp(contents, "{") == 0) { continue; }
    if (strcmp(contents, "}") == 0) { continue; }

    if (strcmp(child->tag, "regex") == 0) { continue; }

    x = lval_add(x, lval_read(child));
  }

  return x;
}

lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  v->cell[v->count-1] = x;

  return v;
}

lval* lval_eval_sexpr(lval* v) {

  for (int i = 0; i < v->count; i++) {
    v->cell[i] = lval_eval(v->cell[i]);
  }

  for (int i = 0; i < v->count; i++) {
    if (v->cell[i]->type == LVAL_ERR) {
      return lval_take(v, i);
    }
  }

  if (v->count == 0) { return v; }

  if (v->count == 1) { return lval_take(v, 0); }

  lval* f = lval_pop(v, 0);
  if (f->type != LVAL_SYM) {
    lval_del(f);
    lval_del(v);

    return lval_err("S-expression does not start with a symbol");
  }

  lval* result = builtin_op(v, f->sym);
  lval_del(f);

  return result;
}

lval* lval_eval(lval* v) {
  if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }

  return v;
}

lval* lval_pop(lval* v, int i) {
  lval* x = v->cell[i];

  memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*) * v->count - i - 1);

  v->count--;

  v->cell = realloc(v->cell, sizeof(lval*) * v->count);

  return x;
}

lval* lval_take(lval* v, int i) {
  lval* x = lval_pop(v, i);
  lval_del(v);
  return x;
}

lval* builtin_op(lval* a, char* op) {
  for (int i = 0; i < a->count; i++) {
    switch (a->cell[i]->type) {
      case LVAL_LONG:
        break;
      case LVAL_DOUBLE:
        break;
      default:
        lval_del(a);
        return lval_err("Can not operate on non-number");
    }
  }

  lval* x = lval_pop(a, 0);
  int is_unary_minus = (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0);

  if (is_unary_minus && a->count == 0) {
    switch (x->type) {
      case LVAL_LONG:
        x->data.l = -x->data.l;
        break;
      case LVAL_DOUBLE:
        x->data.d = -x->data.d;
        break;
      default:
        lval_del(x); lval_del(a);
        return lval_err("Can not apply unary operation to non-number");
    }
  }

  while (a->count > 0) {
    lval* y = lval_pop(a, 0);
    lval* result = NULL;

    switch (x->type) {
      case LVAL_LONG:
        result = builtin_op_long(x, op, y);
        break;
      case LVAL_DOUBLE:
        result = builtin_op_double(x, op, y);
        break;
      default:
        result = lval_err("can not apply operation to a non-number");
        break;
    }

    lval_del(y);

    if (result->type == LVAL_ERR) {
      lval_del(x); lval_del(a);
      return result;
    }

  }

  lval_del(a);
  return x;
}
