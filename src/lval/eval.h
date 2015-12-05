#ifndef LISPY_LVAL_EVAL
#define LISPY_LVAL_EVAL

#include <stdlib.h>
#include "define.h"
#include "operations.h"
#include "functions.h"
#include "math.h"

lval* lval_eval(lval* v);
lval* lval_eval_sexpr(lval* v);

#endif
