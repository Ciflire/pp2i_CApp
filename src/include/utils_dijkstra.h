#include "csv_handler.h"
#include "itineraire_array.h"
#include <math.h>

#ifndef UTILS_DIJKSTRA_H
#define UTILS_DIJKSTRA_H

int get_distance_x_y(borne *bDep, borne *bArr);

int get_charging_time(borne *b, vehicule *v, int max_time_charging);

int get_waiting_time(itineraire_array *it_array, int arrival_time, borne *borne);
#endif
