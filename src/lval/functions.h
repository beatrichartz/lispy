#ifndef LISPY_LVAL_FUNCTIONS
#define LISPY_LVAL_FUNCTIONS

#include <stdlib.h>
#include <stdio.h>
#include "define.h"
#include "eval.h"
#include "operations.h"

#define LISPY_ASSERT(args, condition, err)   \
  if (!(condition)) {                        \
    lval_del(args);                          \
    return lval_err(err);                    \
  }                                          

lval* builtin_head(lval* v);
lval* builtin_tail(lval* v);
lval* builtin_list(lval* v);
lval* builtin_eval(lval* v);
lval* builtin_join(lval* v);

#endif
