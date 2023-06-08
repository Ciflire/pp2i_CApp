#include "../include/timer.h"
#include <time.h>
#include <stdio.h>

clock_t start = 0.000000;
clock_t end = 0.000000;

void timer_start(void) {
  start = clock();
  return;
}

void timer_stop(void) {
    end = clock();
    return;
}

void timer_reset(void) {
    start = 0.000000;
    end = 0.000000;
    return;
}

long timer_get(void) { return (end - start) * 1000 / CLOCKS_PER_SEC; }

void timer_print(void) {
    printf("Time to execute function: %ldms\n", (end -  start) * 1000 / CLOCKS_PER_SEC);
    return;
}
