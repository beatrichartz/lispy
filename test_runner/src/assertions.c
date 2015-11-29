#include "assertions.h"

void assign_file_details(
    test *t,
    const char* file_name,
    int line_number
) {
  if (t->file_name == NULL) {
    t->file_name = strdup(file_name);
  }
  if (t->line_number != line_number) {
    t->line_number = line_number;
  }
}

int execute_test_assertion(
    test *t,
    int assertion,
    const char* assertion_string,
    const char* file_name,
    int line_number
) {
  assign_file_details(t, file_name, line_number);

  if (assertion) {
    pass_assertion(t, assertion_string);
  } else {
    fail_assertion(t, assertion_string);
  }

  return assertion;
}

void execute_mark_as_pending(
    test *t,
    const char* message,
    const char* file_name,
    int line_number
  ) {
  assign_file_details(t, file_name, line_number);
  t->outcome = TEST_PENDING;
  t->pending_message = strdup(message);
}

void pass_assertion(test *t, const char* assertion_string) {
  t->outcome = TEST_PASSED;
}

void fail_assertion(test *t, const char* assertion_string) {
  t->failure_message = malloc(101 * sizeof(char));
  sprintf(t->failure_message, "%s", assertion_string);

  t->outcome = TEST_FAILED;
}
