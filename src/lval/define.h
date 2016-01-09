#pragma once

#include <stdlib.h>
#include <string.h>

union data {
    long l;
    double d;
};

typedef struct lval {
    int type;
    union data data;
    char *err;
    char *sym;
    int count;
    struct lval **cell;
} lval;

enum {
    LVAL_LONG,
    LVAL_DOUBLE,
    LVAL_SYM,
    LVAL_SEXPR,
    LVAL_QEXPR,
    LVAL_ERR
} LVALS;

lval *lval_long(long num);
lval *lval_double(double num);
lval *lval_sym(char *s);
lval *lval_sexpr(void);
lval *lval_qexpr(void);
lval *lval_err(char *m);
