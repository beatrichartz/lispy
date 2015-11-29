#ifndef LISPY_TEST_PARSER
#define LISPY_TEST_PARSER

#include "assertions.h"
#include "lispy.h"

void test_grammar_for_long(test *t);
void test_grammar_for_double(test *t);
void test_grammar_for_symbol(test *t);
void test_grammar_for_sexpr(test *t);
void test_grammar_for_qexpr(test *t);
void test_grammar_for_expr(test *t);
void test_grammar_for_lispy(test *t);

#endif
