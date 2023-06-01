#include <stdbool.h>
#include "utils_dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include "itineraire_array.h"

#define NB_VEHICULES 287
#define BATTERY_MINIMUM 75
#define MAX_TIME_CHARGING 9999
#define MAX_TIME_WAITING 9999


#ifndef PATH_H
#define PATH_H

int path(itineraire_array *itineraires, unsigned int *seed,
         vehicule_list *list_of_all_vehicules,
         bornes_list *list_de_toutes_les_bornes,
         bornes_graph *bg, int *index_of_itineraire);

int pathFinding(bornes_list *path, horaire_list *horaires, bornes_graph *bg,
                  borne *origin, borne *destination, int battery_minimum,
                  int max_time_charging, int max_time_waiting, int actual_time,
                  vehicule *v, itineraire_array *itineraires);

bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum, int max_time_waiting, int actual_time,
                    vehicule *v, int max_time_charging,
                    int *wait_time_at_nearest_neighbour,
                    itineraire_array *itineraires);
#endif
