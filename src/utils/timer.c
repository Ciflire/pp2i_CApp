#include "../include/timer.h"
#include <stdio.h>
#include <time.h>

clock_t start = 0.000000;
clock_t end = 0.000000;

// Set and start the timer
void timer_start(void) {
  start = clock();
  return;
}

// Stop and split the timer
void timer_stop(void) {
  end = clock();
  return;
}

// Get the time elapsed between timer_start and timer_stop
long timer_get(void) { return (end - start) * 1000 / CLOCKS_PER_SEC; }

// Print the time elapsed between timer_start and timer_stop
void timer_print(void) {
  printf("Time to execute function: %ldms\n",
         (end - start) * 1000 / CLOCKS_PER_SEC);
  return;
}

// Reset the timer (set it all to 0)
void timer_reset(void) {
  start = 0.000000;
  end = 0.000000;
  return;
}
