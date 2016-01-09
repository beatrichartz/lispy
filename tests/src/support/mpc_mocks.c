#include "mpc_mocks.h"

mpc_ast_t *mpc_expr_mock(char *type, mpc_ast_t *first, ...) {
    mpc_ast_t *m = mpc_ast_new(type, "");

    va_list arguments;
    mpc_ast_t *x;

    va_start(arguments, first);
    for (x = first; x != NULL; x = va_arg(arguments, mpc_ast_t *)) {
        mpc_ast_add_child(m, x);
    }
    va_end(arguments);

    return m;
}

mpc_ast_t *mpc_content_mock(const char *content) {
    mpc_ast_t *m = mpc_ast_new("content", content);
    return m;
}

mpc_ast_t *mpc_sym_mock(const char *symbol) {
    mpc_ast_t *m = mpc_ast_new("symbol", symbol);
    return m;
}

mpc_ast_t *mpc_double_mock(double number) {
    int number_of_digits = (number > 0.0) ? ((int)log10(number)) : 1;
    char str[number_of_digits + 6];
    sprintf(str, "%4f", number);

    mpc_ast_t *m = mpc_ast_new("double", str);
    return m;
}

mpc_ast_t *mpc_long_mock(long number) {
    int number_of_digits = (number > 0) ? ((int)log10((double)number)) : 1;
    char str[number_of_digits + 1];
    sprintf(str, "%ld", number);

    mpc_ast_t *m = mpc_ast_new("long", str);
    return m;
}
