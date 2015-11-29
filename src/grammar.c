#include "grammar.h"

void define_lispy_grammar() {
  Long     = mpc_new("long");
  Double   = mpc_new("double");
  Symbol   = mpc_new("symbol");
  Sexpr    = mpc_new("sexpr");
  Expr     = mpc_new("expr");
  Lispy    = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
      "                                                  \
      long     : /-?[0-9]+/ ;                            \
      double   : /-?[0-9]+\\.[0-9]+/ ;                   \
      symbol   : '+' | '-' | '*' | '/' | '%' | '^'       \
               | \"add\" | \"sub\" | \"mul\"             \
               | \"div\" | \"mod\" | \"pow\"             \
               | \"max\" | \"min\" ;                     \
      sexpr    : '(' <expr>* ')' ;                       \
      expr     : <double> | <long> | <symbol> | <sexpr> ;\
      lispy    : /^/ <expr>* /$/ ;                       \
      ",
      Long, Double, Symbol, Sexpr, Expr, Lispy);
}

void undefine_lispy_grammar() {
  mpc_cleanup(6, Long, Double, Symbol, Sexpr, Expr, Lispy);
}
