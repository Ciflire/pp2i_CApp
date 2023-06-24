#include "../include/borne.h"
#include <stdlib.h>

// Creates a borne
borne *borne_create(int id, int pdc, int power, double latitude,
                    double longitude) {
  borne *b = malloc(sizeof(borne));
  b->id = id;
  b->pdc = pdc;
  b->power = power;
  b->latitude = latitude;
  b->longitude = longitude;
  b->horairePdc = malloc(pdc * sizeof(horaire_list));
  for (int i = 0; i < pdc; i++) {
    b->horairePdc[i] = horaire_list_create();
  }
  return b;
}

// Destroys a borne
void borne_destroy(borne *b) {
  for (int i = 0; i < b->pdc; i++) {
    horaire_list_destroy(b->horairePdc[i]);
  }
  free(b->horairePdc);
  free(b);
}

// Gets the pdc of a borne
int borne_get_pdc(borne *b) { return b->pdc; }

// Gets the power of a borne
int borne_get_power(borne *b) { return b->power; }

// Gets the latitude of a borne
double borne_get_latitude(borne *b) { return b->latitude; }

// Gets the longitude of a borne
double borne_get_longitude(borne *b) { return b->longitude; }

// Tells if two bornes are equal
// returns 1 if they are equal, 0 otherwise
bool borne_equals(borne *b1, borne *b2) {
  return b1->pdc == b2->pdc && b1->power == b2->power &&
         b1->latitude == b2->latitude && b1->longitude == b2->longitude;
}

// Prints a borne
void borne_print(borne *b) {
  printf("Borne: id=%d, pdc=%d, power=%d, latitude=%lf, longitude=%lf\n", b->id,
         b->pdc, b->power, b->latitude, b->longitude);
}
