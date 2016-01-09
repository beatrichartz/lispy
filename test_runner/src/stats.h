#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct {
  suseconds_t start;
  suseconds_t end;
} stats;

stats* new_stats(void);
void start_stat_run(stats *s);
void end_stat_run(stats *s);
char* time_string_for(stats *s);
void destroy_stats(stats *s);
