#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "define.h"

void print_lval_expr(lval *v, char open, char close);
void print_lval(lval *v);
void println_lval(lval *v);
