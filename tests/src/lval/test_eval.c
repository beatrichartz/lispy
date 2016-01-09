#include "test_eval.h"

void test_lval_eval_simple(test *t) {
    lval *s = lval_sexpr();
    lval_add(s, lval_sym("+"));
    lval_add(s, lval_double(2.2));
    lval_add(s, lval_double(4.4));

    lval *result = lval_eval(s);

    test_assert(result->type == LVAL_DOUBLE);
    test_assert(result->data.d >= 6.59999999);
    test_assert(result->data.d <= 6.60000001);

    lval_del(result);
}

void test_lval_eval_nested(test *t) {
    lval *s = lval_sexpr();
    lval_add(s, lval_sym("/"));
    lval_add(s, lval_long(48));
    lval_add(s, lval_long(4));

    lval *n = lval_sexpr();
    lval_add(s, n);
    lval_add(n, lval_sym("-"));
    lval_add(n, lval_long(5));
    lval_add(n, lval_long(2));

    lval *result = lval_eval(s);

    test_assert(result->type == LVAL_LONG);
    test_assert(result->data.l == 4);

    lval_del(result);
}

void test_lval_eval_error(test *t) {
    lval *s = lval_sexpr();
    lval_add(s, lval_long(48));
    lval_add(s, lval_sym("/"));
    lval_add(s, lval_long(4));

    lval *result = lval_eval(s);

    test_assert(result->type == LVAL_ERR);
    test_assert(
        strcmp(result->err, "S-expression does not start with a symbol") == 0);

    lval_del(result);
}

void test_lval_eval_nested_error(test *t) {
    lval *s = lval_sexpr();
    lval_add(s, lval_sym("/"));
    lval_add(s, lval_long(48));
    lval_add(s, lval_long(4));

    lval *n = lval_sexpr();
    lval_add(s, n);
    lval_add(n, lval_long(5));
    lval_add(n, lval_long(2));
    lval_add(n, lval_sym("-"));

    lval *result = lval_eval(s);

    test_assert(result->type == LVAL_ERR);
    test_assert(
        strcmp(result->err, "S-expression does not start with a symbol") == 0);

    lval_del(result);
}

void test_lval_eval_operations(test *t) {
    char operations[14][5] = {"+",   "-",   "*",   "/",   "%",   "^",   "add",
                              "sub", "mul", "div", "mod", "pow", "min", "max"};

    for (int i = 0; i < 14; i++) {
        char *operation = operations[i];
        lval *s = lval_sexpr();
        lval_add(s, lval_sym(operation));
        lval_add(s, lval_long(48));
        lval_add(s, lval_long(4));

        lval *result = lval_eval(s);

        test_assert(result != NULL);
        test_assert(result->type == LVAL_LONG);

        lval_del(result);
    }
}

void test_lval_eval_list_functions(test *t) {
    char functions[3][5] = {"head", "tail", "init"};

    for (int i = 0; i < 3; i++) {
        char *function = functions[i];
        lval *s = lval_sexpr();
        lval_add(s, lval_sym(function));

        lval *q = lval_qexpr();
        lval_add(s, q);
        lval_add(q, lval_long(48));
        lval_add(q, lval_long(4));

        lval *result = lval_eval(s);

        test_assert(result != NULL);
        test_assert(result->type == LVAL_QEXPR);
        test_assert(result->count == 1);

        lval_del(result);
    }
}

void test_lval_eval_list_function_join(test *t) {
    lval *s = lval_sexpr();
    lval_add(s, lval_sym("join"));

    lval *q = lval_qexpr();
    lval_add(s, q);
    lval_add(q, lval_long(48));
    lval_add(q, lval_long(4));

    lval *r = lval_qexpr();
    lval_add(s, r);
    lval_add(r, lval_long(67));
    lval_add(r, lval_long(5));

    lval *result = lval_eval(s);

    test_assert(result != NULL);
    test_assert(result->type == LVAL_QEXPR);
    test_assert(result->count == 4);

    lval_del(result);
}

void test_lval_eval_list_function_eval(test *t) {
    lval *x = lval_sexpr();
    lval_add(x, lval_sym("eval"));

    lval *a = lval_qexpr();

    lval_add(x, a);
    lval *b = lval_sym("mul");
    lval *c = lval_long(2);
    lval *d = lval_long(3);

    lval_add(a, b);
    lval_add(a, c);
    lval_add(a, d);

    lval *result = lval_eval(x);

    test_assert(result != NULL);
    test_assert(result->type == LVAL_LONG);
    test_assert(result->data.l == 6);

    lval_del(result);
}

void test_lval_eval_list_function_list(test *t) {
    lval *x = lval_sexpr();
    lval_add(x, lval_sym("list"));
    lval_add(x, lval_long(2));
    lval_add(x, lval_long(3));

    lval *result = lval_eval(x);

    test_assert(result != NULL);
    test_assert(result->type == LVAL_QEXPR);
    test_assert(result->count == 2);

    lval_del(result);
}

void test_lval_eval_list_function_cons(test *t) {
    lval *x = lval_sexpr();
    lval_add(x, lval_sym("cons"));
    lval_add(x, lval_long(1));

    lval *a = lval_qexpr();

    lval_add(x, a);
    lval *b = lval_long(2);
    lval *c = lval_long(3);

    lval_add(a, b);
    lval_add(a, c);

    lval *result = lval_eval(x);

    test_assert(result != NULL);
    test_assert(result->type == LVAL_QEXPR);
    test_assert(result->count == 3);

    lval_del(result);
}

void test_lval_eval_list_function_len(test *t) {
    lval *x = lval_sexpr();
    lval_add(x, lval_sym("len"));

    lval *a = lval_qexpr();
    lval_add(x, a);

    lval *b = lval_long(2);
    lval *c = lval_long(3);

    lval_add(a, b);
    lval_add(a, c);

    lval *result = lval_eval(x);

    test_assert(result != NULL);
    test_assert(result->type == LVAL_LONG);
    test_assert(result->data.l == 2);

    lval_del(result);
}
