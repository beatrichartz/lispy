#pragma once

#include "lispy.h"
#include "assertions.h"

void test_list(test *t);
void test_head(test *t);
void test_head_with_too_many_args(test *t);
void test_head_with_wrong_type(test *t);
void test_head_with_empty_list(test *t);
void test_cons(test *t);
void test_cons_with_too_few_args(test *t);
void test_cons_with_too_many_args(test *t);
void test_cons_with_wrong_type(test *t);
void test_tail(test *t);
void test_tail_with_too_many_args(test *t);
void test_tail_with_wrong_type(test *t);
void test_tail_with_empty_list(test *t);
void test_init(test *t);
void test_init_with_too_many_args(test *t);
void test_init_with_wrong_type(test *t);
void test_init_with_empty_list(test *t);
void test_join(test *t);
void test_join_with_wrong_type(test *t);
void test_eval(test *t);
void test_eval_with_too_many_args(test *t);
void test_eval_with_wrong_type(test *t);
void test_len(test *t);
void test_len_with_wrong_type(test *t);
void test_len_with_too_many_args(test *t);
