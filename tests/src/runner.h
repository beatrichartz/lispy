#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define test_assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define run_test(test) do { int r = test(); tests_run++; if (r) { return r; } } while(0)
extern int tests_run;
