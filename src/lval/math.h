#pragma once

#include <stdlib.h>
#include <math.h>

#include "define.h"
#include "operations.h"

lval *builtin_op_long(lval *x, char *op, lval *y);
lval *builtin_op_double(lval *x, char *op, lval *y);
lval *builtin_op(lval *a, char *op);
