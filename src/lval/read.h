#ifndef LISPY_LVAL_READ
#define LISPY_LVAL_READ

#include <stdlib.h>
#include "mpc.h"

#include "define.h"
#include "operations.h"

lval* lval_read(mpc_ast_t* t);

#endif

