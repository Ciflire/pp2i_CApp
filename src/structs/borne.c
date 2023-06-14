#include "../include/borne.h"
#include <stdlib.h>

borne *borne_create(int id, int pdc, int power, double latitude,
                    double longitude) {
  borne *b = malloc(sizeof(borne));
  b->id = id;
  b->pdc = pdc;
  b->power = power;
  b->latitude = latitude;
  b->longitude = longitude;
  b->horairePdc = calloc(pdc, sizeof(horaire_list));
  for (int i = 0; i < pdc; i++) {
    b->horairePdc[i] = horaire_list_create();
  }
  return b;
}

void borne_destroy(borne *b) {
  // printf("Destroying borne %d\n", b->id);
  for (int i = 0; i < b->pdc; i++) {
    // printf("    Destroying horaire_list %d\n", i);
    horaire_list_destroy(b->horairePdc[i]);
  }
  free(b);
}

int borne_get_pdc(borne *b) { return b->pdc; }

int borne_get_power(borne *b) { return b->power; }

double borne_get_latitude(borne *b) { return b->latitude; }

double borne_get_longitude(borne *b) { return b->longitude; }

bool borne_equals(borne *b1, borne *b2) {
  return b1->pdc == b2->pdc && b1->power == b2->power &&
         b1->latitude == b2->latitude && b1->longitude == b2->longitude;
}

void borne_print(borne *b) {
  printf("Borne: id=%d, pdc=%d, power=%d, latitude=%lf, longitude=%lf\n", b->id,
         b->pdc, b->power, b->latitude, b->longitude);
}
