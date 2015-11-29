#ifndef LISPY_TEST_LVAL_MATH
#define LISPY_TEST_LVAL_MATH

#include <stdarg.h>
#include "lispy.h"
#include "support.h"
#include "assertions.h"

void test_lval_double_addition();
void test_lval_double_subtraction();
void test_lval_double_multiplication();
void test_lval_double_division();

void test_lval_double_modulo();
void test_lval_double_power();

void test_lval_double_max();
void test_lval_double_min();

void test_lval_double_unary_minus();

void test_lval_unsupported_double();
void test_lval_unsupported_double_unary();


void test_lval_long_addition();
void test_lval_long_subtraction();
void test_lval_long_multiplication();
void test_lval_long_division();

void test_lval_long_modulo();
void test_lval_long_power();

void test_lval_long_max();
void test_lval_long_min();

void test_lval_long_unary_minus();

void test_lval_unsupported_long();
void test_lval_unsupported_long_unary();

#endif
