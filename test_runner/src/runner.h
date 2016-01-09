#pragma once

#include <stdio.h>
#include <sys/time.h>
#include <execinfo.h>
#include "colors.h"
#include "assertions.h"
#include "test.h"
#include "suite.h"
#include "stats.h"
#include "lispy.h"

typedef struct {
  int run;
  int pending;
  int passed;
  int failed;
  int seed;
} runner;

runner* new_runner(void);
void run_suite(runner *r, suite *s, stats *st);
void run_test(runner *r, test *t);
void print_run_start(runner *r, suite *s);
void print_run_result(runner *r, suite *s);
void print_run_failures(runner *r, suite *s);
void print_run_info(runner *r, suite *s, stats *st);
void destroy_runner(runner *r);
