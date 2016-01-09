#include "stats.h"

stats *new_stats(void) {
    stats *s = malloc(sizeof(stats));
    return s;
}

void start_stat_run(stats *s) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    s->start = tv.tv_usec;
}

void end_stat_run(stats *s) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    s->end = tv.tv_usec;
}

char *time_string_for(stats *s) {
    char *message = malloc(sizeof(char) * 100);
    if ((s->end - s->start) < 1000) {
        sprintf(message, "%d µs", s->end - s->start);
    } else if ((s->end - s->start) < 1000000) {
        sprintf(message, "%d ms", (s->end - s->start) / 1000);
    } else {
        sprintf(message, "%d s", (s->end - s->start) / 1000000);
    }

    return message;
}

void destroy_stats(stats *s) {
    free(s);
}
