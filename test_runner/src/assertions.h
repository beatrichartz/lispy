#ifndef RUNNER_ASSERTIONS
#define RUNNER_ASSERTIONS

#include <stdio.h>
#include <strings.h>
#include "colors.h"
#include "test.h"

int execute_test_assertion(
    test *t,
    int assertion,
    const char* assertion_string,
    const char* file_name,
    int line_number
);

void execute_mark_as_pending(
    test *t,
    const char* message,
    const char* file_name,
    int line_number
);

void pass_assertion(test *t, const char* assertion_string);
void fail_assertion(test *t, const char* assertion_string);

#define pending(message) do {                        \
  execute_mark_as_pending(                           \
      t,                                             \
      message,                                       \
      __FILE__,                                      \
      __LINE__                                       \
  );                                                 \
                                                     \
  return;                                            \
} while(0);

#define test_assert_message(                         \
    assertion,                                       \
    message                                          \
  ) do {                                             \
  int _assertion_result_ = execute_test_assertion(   \
      t,                                             \
      assertion,                                     \
      message,                                       \
      __FILE__,                                      \
      __LINE__                                       \
  );                                                 \
                                                     \
  if (!_assertion_result_) {                         \
    return;                                          \
  }                                                  \
} while(0)

#define test_assert_auto_message(assertion)          \
  test_assert_message(assertion, #assertion)

#define test_assert_custom_message(                  \
    assertion, message                               \
)                                                    \
  test_assert_message(                               \
      assertion,                                     \
      message                                        \
  )

#define test_assert_custom_interpolated_message(     \
    assertion, message, ...                          \
)                                                    \
  char _message_[1024];                              \
  sprintf(_message_, message, __VA_ARGS__);          \
  test_assert_message(                               \
      assertion,                                     \
      _message_                                      \
  )                                                  \

#pragma clang diagnostic ignored                     \
  "-Wgnu-zero-variadic-macro-arguments"
#define _get_assert_(                                \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,        \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,        \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,        \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,        \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,        \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,        \
     _61,_62,_63, NAME, ...) NAME

#define test_assert(...)                             \
  _get_assert_(                                      \
      __VA_ARGS__,                                   \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_interpolated_message,       \
      test_assert_custom_message,                    \
      test_assert_auto_message                       \
  )(__VA_ARGS__)

#endif
