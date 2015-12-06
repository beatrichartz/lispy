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
  int size = s->focused_tests > 0 ? s->focused_tests : (s->size - s->crossed_tests);
  printf(
      "\n%s**************************************\
 RUNNING %4.1d TESTS\
 ***************************************%s\n\n",
      KCYN, size, RESET);
}

void print_run_result(runner *r, suite *s) {
  char* color = (r->failed == 0) ? (r->pending == 0) ? KGRN : KYLW : KRED;
  char* message = "\n%s*********************\
 %4.1d TEST RUN, %4.1d PASSED, %4.1d PENDING, %4.1d FAILED\
 ********************%s\n";
  int run = s->focused_tests == 0 ? r->run : s->focused_tests;
  printf(message, color, run, r->passed, r->pending, r->failed, RESET);
}

void print_run_pending(runner *r, suite *s) {
  if (r->pending == 0) { return; }

  for (int i = 0; i < s->size; i++) {
    test *t = s->tests[i];
    if (t->outcome == TEST_FAILED) { continue; }
    if (t->outcome == TEST_PASSED) { continue; }
    if (s->focused_tests > 0 && !t->focused) { continue; }
    if (s->crossed_tests > 0 && t->crossed)  { continue; }
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
    printf("%sfailed assertion: %s\n%s\n%s:%d%s\n\n" , KRED, t->failure_message, t->func_name, t->file_name, t->line_number, RESET);
  }
  printf("\n");
}

void print_run_info(runner *r, suite *s, stats *st) {
  char *time = time_string_for(st);
  printf("\n%sRandomized with seed %6.1d - Run took %s%s\n\n" , KCYN, r->seed, time, RESET);
  free(time);
}

int should_run_test(suite *s, test *t) {
  return (
      (
       (s->focused_tests > 0 && t->focused) ||
       (s->focused_tests == 0)
      ) && !t->crossed
   );
}

void run_suite(runner *r, suite *s, stats *st) {
  start_stat_run(st);
  r->seed = st->start;

  randomize_suite(s, r->seed);

  print_run_start(r, s);

  for (int i = 0; i < s->size; i++) {
    test *t = s->tests[i];
    if (should_run_test(s, t)) {
      run_test(r, t);
    }
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
  suite* s = new_suite(20);

  add_tests(s);

  runner* r = new_runner();
  stats *st = new_stats();

  run_suite(r, s, st);

  int failed = r->failed > 0;

  destroy_runner(r);
  destroy_suite(s);
  destroy_stats(st);

  return failed;
}
