#include <stdbool.h>
#include "utils_dijkstra.h"
#include <stdio.h>
#include <stdlib.h>


#ifndef PATH_H
#define PATH_H
int main(void);
bornes_list *pathFinding(bornes_graph *bg, borne *origin, borne *destination,
                         int battery_minimum, int max_time_charging,
                         int max_time_waiting,
                         /*int actual_time, */vehicule *v);

bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum, int max_time_waiting, /*int actual_time,*/
                    vehicule *v, int max_time_charging);
#endif
