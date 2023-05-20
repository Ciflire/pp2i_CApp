#include "csv_handler.h"
#include <math.h>

#ifndef UTILS_DIJKSTRA_H
#define UTILS_DIJKSTRA_H

int get_distance_x_y(borne *bDep, borne *bArr);

int get_charging_time(borne *b, vehicule *v, int max_time_charging);

#endif
