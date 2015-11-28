#ifndef LISPY_LVAL_OPERATIONS
#define LISPY_LVAL_OPERATIONS

#include <stdlib.h>
#include <stdio.h>
#include "define.h"

lval* lval_add(lval* v, lval* x);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
void lval_del(lval* v);

#endif
