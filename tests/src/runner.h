#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define PRINT_RUN_START()                                              \
  printf("\n%s*** RUNNING TESTS ***%s\n\n", KYEL, RESET);

#define PRINT_RUN_RESULT() do {                                        \
  char* color = (tests_failed == 0) ? KGRN : KRED;                     \
  char* message = "\n%s*** %d TEST RUN, %d PASSED, %d FAILED ***%s\n"; \
  printf(message, color, tests_run, tests_passed, tests_failed, RESET);\
} while(0)

#define PASS() do {                                                    \
  tests_passed++;                                                      \
  printf("%sPASSED: %s()%s\n", KGRN, __func__, RESET);                 \
} while(0)

#define FAIL() do {                                                    \
  tests_failed++;                                                      \
  printf("%sFAILED: %s()%s\n", KRED, __func__, RESET);                 \
} while(0)

#define test_assert(test) do {                                         \
  if (test) {                                                          \
    PASS();                                                            \
  } else {                                                             \
    FAIL();                                                            \
  }                                                                    \
} while(0)

#define run_test(test) do {                                            \
  int r = test();                                                      \
  tests_run++;                                                         \
  if (r) { return r; }                                                 \
} while(0)

extern int tests_run;
extern int tests_passed;
extern int tests_failed;
