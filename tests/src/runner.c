#include "runner.h"

runner* new_runner() {
  runner *r = malloc(sizeof(runner));
  r->run = 0;
  r->pending = 0;
  r->passed = 0;
  r->failed = 0;

  return r;
}

void destroy_runner(runner *r) {
  free(r);
  r = NULL;
}

void print_run_start(runner *r, suite *s) {
  printf(
      "\n%s**************************************\
 RUNNING %4.1zu TESTS\
 ***************************************%s\n\n",
      KCYN, s->size, RESET);
}

void print_run_result(runner *r, suite *s) {
  char* color = (r->failed == 0) ? (r->pending == 0) ? KGRN : KYLW : KRED;
  char* message = "\n%s*********************\
 %4.1d TEST RUN, %4.1d PASSED, %4.1d PENDING, %4.1d FAILED\
 ********************%s\n";
  printf(message, color, r->run, r->passed, r->pending, r->failed, RESET);
}

void print_run_pending(runner *r, suite *s) {
  if (r->pending == 0) { return; }

  for (int i = 0; i < s->size; i++) {
    test *t = s->tests[i];
    if (t->outcome == TEST_FAILED) { continue; }
    if (t->outcome == TEST_PASSED) { continue; }
    printf("%s%s is pending: %s%s\n" , KYLW, t->func_name, t->pending_message, RESET);
  }
  printf("\n");
}

void print_run_failures(runner *r, suite *s) {
  if (r->failed == 0) { return; }

  for (int i = 0; i < s->size; i++) {
    test *t = s->tests[i];
    if (t->outcome == TEST_PASSED) { continue; }
    if (t->outcome == TEST_PENDING) { continue; }
    printf("%s%s failed assertion: %s%s\n" , KRED, t->func_name, t->failure_message, RESET);
  }
  printf("\n");
}

void print_run_info(runner *r, suite *s, stats *st) {
  char *ms = microseconds_string_for(st);
  printf("\n%sRandomized with seed %6.1d - Run took %s%s\n\n" , KCYN, r->seed, ms, RESET);
  free(ms);
}


void run_suite(runner *r, suite *s, stats *st) {
  start_stat_run(st);
  r->seed = st->start;

  randomize_suite(s, r->seed);

  print_run_start(r, s);

  for (int i = 0; i < s->size; i++) {
    test *t = s->tests[i];
    run_test(r, t);
  }

  end_stat_run(st);

  print_run_result(r, s);
  print_run_info(r, s, st);
  print_run_pending(r, s);
  print_run_failures(r, s);
}


void run_test(runner *r, test *t) {
  t->func(t);
  r->run++;

  switch (t->outcome) {
    case TEST_PASSED:
      r->passed++;
      printf("%s%-90spassed%s\n", KGRN, t->func_name, RESET);
      break;
    case TEST_FAILED:
      r->failed++;
      printf("%s%-90sfailed%s\n", KRED, t->func_name, RESET);
      break;
    case TEST_PENDING:
      r->pending++;
      printf("%s%-90spending%s\n", KYLW, t->func_name, RESET);
      break;
  }
}

int main(int arc, char** argv) {
  suite* s = add_all_tests();
  runner* r = new_runner();
  stats *st = new_stats();

  run_suite(r, s, st);

  int failed = r->failed > 0;

  destroy_runner(r);
  destroy_suite(s);
  destroy_stats(st);

  return failed;
}
