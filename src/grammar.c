#include "grammar.h"

void define_lispy_grammar() {
  Long     = mpc_new("long");
  Double   = mpc_new("double");
  Symbol   = mpc_new("symbol");
  Sexpr    = mpc_new("sexpr");
  Qexpr    = mpc_new("qexpr");
  Expr     = mpc_new("expr");
  Lispy    = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
      "                                                  \
      long     : /-?[0-9]+/ ;                            \
      double   : /-?[0-9]+\\.[0-9]+/ ;                   \
      symbol   : '+' | '-' | '*' | '/' | '%' | '^'       \
               | \"add\" | \"sub\" | \"mul\"             \
               | \"div\" | \"mod\" | \"pow\"             \
               | \"max\" | \"min\"                       \
               | \"list\" | \"head\" | \"tail\"          \
               | \"join\" | \"eval\" | \"cons\"          \
               | \"len\" ;                               \
      sexpr    : '(' <expr>* ')' ;                       \
      qexpr    : '{' <expr>* '}' ;                       \
      expr     : <double> | <long> | <symbol> | <sexpr>  \
               | <qexpr>;                                \
      lispy    : /^/ <expr>* /$/ ;                       \
      ",
      Long, Double, Symbol, Sexpr, Qexpr, Expr, Lispy);
}

void undefine_lispy_grammar() {
  mpc_cleanup(7, Long, Double, Symbol, Sexpr, Qexpr, Expr, Lispy);
}
