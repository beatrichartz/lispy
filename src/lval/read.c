#include "read.h"

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
  if (strstr(t->tag, "qexpr"))  { x = lval_qexpr(); }

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

