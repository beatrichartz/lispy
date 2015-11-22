#include "repl.h"

int repl(int argc, char** argv) {
  mpc_parser_t* Long     = mpc_new("long");
  mpc_parser_t* Double   = mpc_new("double");
  mpc_parser_t* Symbol   = mpc_new("symbol");
  mpc_parser_t* Sexpr    = mpc_new("sexpr");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Lispy    = mpc_new("lispy");

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

  puts("LISPY version 0.0.1");
  puts("Press CTRL-c to exit");

  while(1) {
    char* input = readline("LISPY> ");
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      add_history(input);

      lval* result = lval_eval(lval_read(r.output));
      println_lval(result);
      lval_del(result);

      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(6, Long, Double, Symbol, Sexpr, Expr, Lispy);

  return 0;
}
