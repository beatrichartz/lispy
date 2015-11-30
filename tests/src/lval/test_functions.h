#ifndef LISPY_TEST_LVAL_FUNCTIONS
#define LISPY_TEST_LVAL_FUNCTIONS

#include "lispy.h"
#include "assertions.h"

void test_list(test *t);
void test_head(test *t);
void test_head_with_too_many_args(test *t);
void test_head_with_wrong_type(test *t);
void test_head_with_empty_list(test *t);
void test_tail(test *t);
void test_join(test *t);
void test_eval(test *t);

#endif
