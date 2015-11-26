#ifndef LISPY_TEST_LVAL_MATH
#define LISPY_TEST_LVAL_MATH

#include <stdarg.h>
#include "lispy.h"
#include "support.h"
#include "assertions.h"

int test_lval_double_addition();
int test_lval_double_subtraction();
int test_lval_double_multiplication();
int test_lval_double_division();

int test_lval_double_modulo();
int test_lval_double_power();

int test_lval_double_max();
int test_lval_double_min();

int test_lval_double_unary_minus();

int test_lval_unsupported_double();
int test_lval_unsupported_double_unary();


int test_lval_long_addition();
int test_lval_long_subtraction();
int test_lval_long_multiplication();
int test_lval_long_division();

int test_lval_long_modulo();
int test_lval_long_power();

int test_lval_long_max();
int test_lval_long_min();

int test_lval_long_unary_minus();

int test_lval_unsupported_long();
int test_lval_unsupported_long_unary();

#endif
