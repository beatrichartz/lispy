#include "parser.h"

void parse_lispy(char *input, parse_cb success_cb, parse_cb error_cb) {
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
        success_cb(&r);
        mpc_ast_delete(r.output);
    } else {
        error_cb(&r);
        mpc_err_delete(r.error);
    }
}
