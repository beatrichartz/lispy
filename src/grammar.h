#ifndef LISPY_GRAMMAR
#define LISPY_GRAMMAR

#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

mpc_parser_t* Long;
mpc_parser_t* Double;
mpc_parser_t* Symbol;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;

void define_lispy_grammar();
void undefine_lispy_grammar();

#endif
