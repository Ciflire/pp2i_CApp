#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/horaire_list.h"

#ifndef BORNE_H

#define BORNE_H

struct borne {
  int id;
  int pdc;
  int power;
  double latitude;
  double longitude;
  horaire_list **horaires_pdc;
};

typedef struct borne borne;

// Creates a borne
borne *borne_create(int id, int pdc, int power, double latitude, double longitude);

// Destroys a borne
void borne_destroy(borne *b);

// Gets the pdc of a borne
int borne_get_pdc(borne *b);

// Gets the power of a borne
int borne_get_power(borne *b);

// Gets the latitude of a borne
double borne_get_latitude(borne *b);

// Gets the longitude of a borne
double borne_get_longitude(borne *b);

// Tells if two bornes are equal
// returns 1 if they are equal, 0 otherwise
bool borne_equals(borne *b1, borne *b2);

// Prints a borne
void borne_print(borne *b);

#endif
