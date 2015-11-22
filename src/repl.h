#ifndef LISPY_REPL
#define LISPY_REPL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <editline/readline.h>
#include "parser.h"
#include "lval.h"
#include "mpc.h"

int repl(int argc, char** argv);

#endif
