#include "test_print.h"

void test_lval_print_sexpr(test *t) {
    lval *e = lval_sexpr();
    lval_add(e, lval_sym("+"));
    lval_add(e, lval_double(2.2));
    lval_add(e, lval_double(4.4));

    freopen("tests/tmp/captured_output", "w", stdout);
    print_lval(e);
    freopen("/dev/tty", "w", stdout);

    FILE *captured_output = fopen("tests/tmp/captured_output", "r");
    char string[22];
    fgets(string, 22, captured_output);
    fclose(captured_output);

    test_assert(strcmp(string, "(+ 2.200000 4.400000)") == 0);

    lval_del(e);
}

void test_lval_print_qexpr(test *t) {
    lval *e = lval_qexpr();
    lval_add(e, lval_double(2.2));
    lval_add(e, lval_double(4.4));

    freopen("tests/tmp/captured_output", "w", stdout);
    print_lval(e);
    freopen("/dev/tty", "w", stdout);

    FILE *captured_output = fopen("tests/tmp/captured_output", "r");
    char string[20];
    fgets(string, 20, captured_output);
    fclose(captured_output);

    test_assert(strcmp(string, "{2.200000 4.400000}") == 0);

    lval_del(e);
}

void test_lval_print_long(test *t) {
    lval *e = lval_long(2);

    freopen("tests/tmp/captured_output", "w", stdout);
    print_lval(e);
    freopen("/dev/tty", "w", stdout);

    FILE *captured_output = fopen("tests/tmp/captured_output", "r");
    char string[2];
    fgets(string, 2, captured_output);
    fclose(captured_output);

    test_assert(strcmp(string, "2") == 0);

    lval_del(e);
}
void test_lval_print_double(test *t) {
    lval *e = lval_double(2.2);

    freopen("tests/tmp/captured_output", "w", stdout);
    print_lval(e);
    freopen("/dev/tty", "w", stdout);

    FILE *captured_output = fopen("tests/tmp/captured_output", "r");
    char string[9];
    fgets(string, 9, captured_output);
    fclose(captured_output);

    test_assert(strcmp(string, "2.200000") == 0);

    lval_del(e);
}
