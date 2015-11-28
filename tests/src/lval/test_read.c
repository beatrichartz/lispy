#include "test_read.h"

mpc_ast_t* test_mpc_ast() {
  mpc_ast_t *s = mpc_sexpr_mock(
      mpc_content_mock("("),
      mpc_sym_mock("+"),
      mpc_long_mock(1),
      mpc_long_mock(2),
      mpc_sexpr_mock(
        mpc_content_mock("("),
        mpc_sym_mock("mul"),
        mpc_long_mock(3),
        mpc_long_mock(4),
        mpc_content_mock(")"),
        NULL
      ),
      mpc_content_mock(")"),
      NULL
  );

  return s;
}

int test_lval_read_sexpr() {
  mpc_ast_t *s = test_mpc_ast();

  lval *result = lval_read(s);

  test_assert(result->count == 4);
  test_assert(result->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(result->cell[0]->sym, "+") == 0);

  test_assert(result->cell[1]->type == LVAL_LONG);
  test_assert(result->cell[1]->data.l == 1);

  test_assert(result->cell[2]->type == LVAL_LONG);
  test_assert(result->cell[2]->data.l == 2);

  test_assert(result->cell[3]->type == LVAL_SEXPR);
  test_assert(result->cell[3]->count == 3);

  return 1;
}

int test_lval_read_sub_sexpr() {
  mpc_ast_t *s = test_mpc_ast();

  lval *result = lval_read(s);

  test_assert(result->count == 4);

  test_assert(result->cell[3]->type == LVAL_SEXPR);
  test_assert(result->cell[3]->count == 3);

  lval *subresult = result->cell[3];
  test_assert(subresult->count == 3);

  test_assert(subresult->cell[0]->type == LVAL_SYM);
  test_assert(strcmp(subresult->cell[0]->sym, "mul") == 0);

  test_assert(subresult->cell[1]->type == LVAL_LONG);
  test_assert(subresult->cell[1]->data.l == 3);

  test_assert(subresult->cell[2]->type == LVAL_LONG);
  test_assert(subresult->cell[2]->data.l == 4);

  return 1;
}

int test_lval_read_double() {
  mpc_ast_t *s = mpc_double_mock(2.33);
  lval *result = lval_read(s);

  test_assert(result->type == LVAL_DOUBLE);
  test_assert(result->data.d <= 2.330001);
  test_assert(result->data.d >= 2.329999);
  return 1;
}

int test_lval_read_long() {
  mpc_ast_t *s = mpc_long_mock(2);
  lval *result = lval_read(s);

  test_assert(result->type == LVAL_LONG);
  test_assert(result->data.l == 2);
  return 1;
}
