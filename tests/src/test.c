#include "test.h"

test* new_test(testfunc func, const char* func_name) {
  test *t = malloc(sizeof(test));
  t->func = func;
  t->outcome = TEST_PENDING;
  t->func_name = strdup(func_name);
  t->file_name = NULL;
  t->line_number = 0;
  t->failure_message = NULL;
  t->pending_message = strdup("no assertions yet");

  return t;
}

void destroy_string_field(char *s) {
  if (s != NULL) {
    free(s);
    s = NULL;
  }
}

void destroy_test(test *t) {
  destroy_string_field(t->func_name);
  destroy_string_field(t->file_name);
  destroy_string_field(t->failure_message);
  destroy_string_field(t->pending_message);
  free(t);
  t = NULL;
}
