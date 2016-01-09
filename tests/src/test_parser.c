#include "test_parser.h"

lval *result;
void success_cb(mpc_result_t *ast) {
  /* The parser immediately deletes the ast, */
  /* so we store it in a variable */
  result = lval_read(ast->output);
}
void error_cb(mpc_result_t *error) {}

void setup_parser() {
  define_lispy_grammar();
  result = NULL;
}
void teardown_parser() {
  lval_del(result);
  result = NULL;
  undefine_lispy_grammar();
}

void test_grammar_for_long(test *t) {
  setup_parser();
  char* input = "1234";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->cell[0]->type == LVAL_LONG);
  test_assert(result->cell[0]->data.l == 1234);

  teardown_parser();
}
void test_grammar_for_double(test *t) {
  setup_parser();
  char* input = "1234.0";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->cell[0]->type == LVAL_DOUBLE);
  test_assert(result->cell[0]->data.d == 1234.0);

  teardown_parser();
}
void test_grammar_for_symbol(test *t) {
  char symbols[22][5] = { "+", "-", "*", "/", "%", "^",
    "add", "sub", "mul", "div", "mod", "pow",
    "min", "max",
    "list", "head", "tail", "join", "eval", "cons", "len", "init"
  };

  for (int i = 0; i < 22; i++) {
    setup_parser();
    char *input = symbols[i];

    parse_lispy(input, success_cb, error_cb);
    test_assert(result != NULL);
    test_assert(result->type == LVAL_SEXPR);
    test_assert(result->cell[0]->type == LVAL_SYM);
    test_assert(strcmp(result->cell[0]->sym, input) == 0);
    teardown_parser();
  }
}

void test_grammar_for_sexpr(test *t) {
  setup_parser();
  char *input = "(- 1234.0 2.0)";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->count == 1);

  lval *subresult = result->cell[0];
  test_assert(subresult->type == LVAL_SEXPR);
  test_assert(subresult->count == 3);

  test_assert(subresult->cell[0]->type == LVAL_SYM);
  test_assert(subresult->cell[1]->type == LVAL_DOUBLE);
  test_assert(subresult->cell[2]->type == LVAL_DOUBLE);

  teardown_parser();
}

void test_grammar_for_qexpr(test *t) {
  setup_parser();
  char *input = "head {1 2 3 4}";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->count == 2);

  test_assert(result->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(result->cell[0]->sym, "head") == 0);

  lval *subresult = result->cell[1];
  test_assert(subresult->type == LVAL_QEXPR);
  test_assert(subresult->count == 4);

  test_assert(subresult->cell[0]->type == LVAL_LONG);
  test_assert(subresult->cell[1]->type == LVAL_LONG);
  test_assert(subresult->cell[2]->type == LVAL_LONG);
  test_assert(subresult->cell[3]->type == LVAL_LONG);

  teardown_parser();
}

void test_grammar_for_expr(test *t) {
  setup_parser();
  char *input = "- 1234.0 2.0";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->count == 3);

  test_assert(result->cell[0]->type == LVAL_SYM);
  test_assert(result->cell[1]->type == LVAL_DOUBLE);
  test_assert(result->cell[2]->type == LVAL_DOUBLE);

  teardown_parser();
}
void test_grammar_for_lispy(test *t) {
  setup_parser();
  char *input = "sub 1234 (* 2 (/ 3 2))";

  parse_lispy(input, success_cb, error_cb);
  test_assert(result != NULL);
  test_assert(result->type == LVAL_SEXPR);
  test_assert(result->count == 3);

  test_assert(result->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(result->cell[0]->sym, "sub") == 0);

  test_assert(result->cell[1]->type == LVAL_LONG);
  test_assert(result->cell[1]->data.l == 1234);

  lval *subresult = result->cell[2];
  test_assert(subresult->type == LVAL_SEXPR);
  test_assert(subresult->count == 3);

  test_assert(subresult->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(subresult->cell[0]->sym, "*") == 0);
  test_assert(subresult->cell[1]->type == LVAL_LONG);
  test_assert(subresult->cell[1]->data.l == 2);

  lval *subsubresult = subresult->cell[2];
  test_assert(subsubresult->type == LVAL_SEXPR);
  test_assert(subsubresult->count == 3);

  test_assert(subsubresult->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(subsubresult->cell[0]->sym, "/") == 0);
  test_assert(subsubresult->cell[1]->type == LVAL_LONG);
  test_assert(subsubresult->cell[1]->data.l == 3);

  test_assert(subsubresult->cell[2]->type == LVAL_LONG);
  test_assert(subsubresult->cell[2]->data.l == 2);

  teardown_parser();
}
