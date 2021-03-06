#pragma once

#include "lispy.h"
#include "assertions.h"

void test_lval_eval_simple(test *t);
void test_lval_eval_nested(test *t);
void test_lval_eval_error(test *t);
void test_lval_eval_nested_error(test *t);
void test_lval_eval_operations(test *t);
void test_lval_eval_list_functions(test *t);
void test_lval_eval_list_function_join(test *t);
void test_lval_eval_list_function_eval(test *t);
void test_lval_eval_list_function_list(test *t);
void test_lval_eval_list_function_cons(test *t);
void test_lval_eval_list_function_len(test *t);
