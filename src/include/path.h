#include "utils_dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef PATH_H
#define PATH_H
int main(int argc, char *argv[]);
bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum, int max_time_waiting, int actual_time,
                    vehicule *v, int max_time_charging);
#endif
