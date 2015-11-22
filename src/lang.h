#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <editline/readline.h>
#include "mpc.h"

union data {
  long l;
  double d;
};

typedef struct lval {
  int type;
  union data data;
  char* err;
  char* sym;
  int count;
  struct lval** cell;
} lval;

enum {
  LVAL_LONG,
  LVAL_DOUBLE,
  LVAL_SYM,
  LVAL_SEXPR,
  LVAL_ERR
} LVALS;

lval* lval_long(long num);
lval* lval_double(double num);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
lval* lval_err(char* m);
void lval_del(lval* v);
void print_lval_expr(lval* v, char open, char close);
void print_lval(lval* v);
void println_lval(lval* v);
lval* builtin_op_long(lval* x, char* op, lval* y);
lval* builtin_op_double(lval* x, char* op, lval* y);
lval* lval_read_long(mpc_ast_t* t);
lval* lval_read_double(mpc_ast_t* t);
lval* lval_add(lval* v, lval* x);
lval* lval_read(mpc_ast_t* t);
lval* lval_eval(lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_add(lval* v, lval* x);
lval* builtin_op(lval* a, char* op);
lval* lval_eval_sexpr(lval* v);

void print_lval(lval* v);
