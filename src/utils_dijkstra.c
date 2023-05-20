#include "include/utils_dijkstra.h"

int get_distance_x_y(borne *bDep, borne *bArr) {
  double R = 6371;
  double varLong = (bArr->xpos - bDep->xpos) * M_PI / 180;
  double varLat = (bArr->ypos - bDep->ypos) * M_PI / 180;
  double a = sin(varLat / 2) * sin(varLat / 2) +
             cos(bDep->ypos * M_PI / 180) * cos(bArr->ypos * M_PI / 180) *
                 sin(varLong / 2) * sin(varLong / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int d = (int)R * c;
  return d;
}
