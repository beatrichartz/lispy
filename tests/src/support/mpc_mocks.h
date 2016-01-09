#pragma once

#include "lispy.h"

mpc_ast_t *mpc_expr_mock(char *type, mpc_ast_t *first, ...);
mpc_ast_t *mpc_content_mock(const char *content);
mpc_ast_t *mpc_sym_mock(const char *symbol);
mpc_ast_t *mpc_double_mock(double number);
mpc_ast_t *mpc_long_mock(long number);
