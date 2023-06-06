#include "../include/timer.h"
#include <time.h>
#include <stdio.h>

clock_t start = 0.000000;
clock_t end = 0.000000;

void timer_start(){
    start = clock();
    return;
}

void timer_stop(){
    end = clock();
    return;
}

void timer_reset(){
    start = 0.000000;
    end = 0.000000;
    return;
}

long timer_get(){
    return (end -  start) * 1000 / CLOCKS_PER_SEC;
}

void timer_print(){
    printf("Time to execute function: %ldms\n", (end -  start) * 1000 / CLOCKS_PER_SEC);
    return;
}
