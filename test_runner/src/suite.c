#include "suite.h"

suite *new_suite(size_t initial_capacity) {
    suite *s = malloc(sizeof(suite));
    ;
    s->size = 0;
    s->capacity = initial_capacity;
    s->tests = (test **)malloc(initial_capacity * sizeof(test *));
    s->crossed_tests = 0;
    s->focused_tests = 0;
    if (s->tests == NULL) {
        printf("Failed to allocate tests array\n");
        exit(1);
    }

    return s;
}

void execute_add_test_to_suite(suite *s, testfunc func, const char *func_name,
                               int focused, int crossed) {
    if (s->capacity == s->size) {
        s->capacity *= 2;
        s->tests = (test **)realloc(s->tests, s->capacity * sizeof(test *));
        if (s->tests == NULL) {
            printf("Failed to allocate tests array\n");
            exit(1);
        }
    }

    test *t = new_test(func, func_name, focused, crossed);
    s->tests[s->size++] = t;
    if (focused) {
        s->focused_tests++;
    }
    if (crossed) {
        s->crossed_tests++;
    }
}

void destroy_suite(suite *s) {
    for (int i = 0; i < s->size; i++) {
        destroy_test(s->tests[i]);
    }
    free(s->tests);
    s->tests = NULL;
    s->capacity = 0;
    s->size = 0;
    free(s);
    s = NULL;
}

void randomize_suite(suite *s, int seed) {
    srand48(seed);

    for (int i = 0; i < s->size; i++) {
        size_t j = (unsigned int)(drand48() * (i + 1));
        test *t = s->tests[j];
        s->tests[j] = s->tests[i];
        s->tests[i] = t;
    }
}
