#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "define.h"

char LISPY_OPERATIONS[19][5];

lval* lval_add(lval* v, lval* x);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
void lval_del(lval* v);
