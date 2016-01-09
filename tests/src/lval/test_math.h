#pragma once

#include <stdarg.h>
#include "lispy.h"
#include "support.h"
#include "assertions.h"

void test_lval_double_addition(test *t);
void test_lval_double_subtraction(test *t);
void test_lval_double_multiplication(test *t);
void test_lval_double_division(test *t);

void test_lval_double_modulo(test *t);
void test_lval_double_power(test *t);

void test_lval_double_max(test *t);
void test_lval_double_min(test *t);

void test_lval_double_unary_minus(test *t);

void test_lval_unsupported_double(test *t);
void test_lval_unsupported_double_unary(test *t);


void test_lval_long_addition(test *t);
void test_lval_long_subtraction(test *t);
void test_lval_long_multiplication(test *t);
void test_lval_long_division(test *t);

void test_lval_long_modulo(test *t);
void test_lval_long_power(test *t);

void test_lval_long_max(test *t);
void test_lval_long_min(test *t);

void test_lval_long_unary_minus(test *t);

void test_lval_unsupported_long(test *t);
void test_lval_unsupported_long_unary(test *t);
