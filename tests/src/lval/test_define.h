#pragma once

#include "lispy.h"
#include "assertions.h"

void test_lval_long(test *t);
void test_lval_double(test *t);
void test_lval_sym(test *t);
void test_lval_sexpr(test *t);
void test_lval_qexpr(test *t);
void test_lval_err(test *t);
