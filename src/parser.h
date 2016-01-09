#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "grammar.h"
#include "mpc.h"

typedef void (*parse_cb)(mpc_result_t *r);
void parse_lispy(char *input, parse_cb success_cb, parse_cb error_cb);
