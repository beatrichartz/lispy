#include "repl.h"

void eval_ast(mpc_result_t* ast) {
  lval* result = lval_eval(lval_read(ast->output));
  println_lval(result);
  lval_del(result);
}

void eval_err(mpc_result_t* err) {
  mpc_err_print(err->error);
}

int repl(int argc, char** argv) {
  define_lispy_grammar();

  puts("LISPY version 0.0.1");
  puts("Press CTRL-c to exit");

  while(1) {
    char* input = readline("LISPY> ");
    add_history(input);

    parse_lispy(input, eval_ast, eval_err);

    free(input);
  }

  undefine_lispy_grammar();
  return 0;
}
