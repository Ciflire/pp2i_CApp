/*
Lsite itinéraire tableau d'itinéraire
*/

#include "itineraire.h"

#ifndef ITINERAIRE_ARRAY_H

#define ITINERAIRE_ARRAY_H

struct itineraire_array {
  int size;
  itineraire **array;
};

typedef struct itineraire_array itineraire_array;

// Create itinéraire_array of size size
itineraire_array *itineraire_array_new(int size);

// Destroy itinéraire_array
void destroy_itineraire_array(itineraire_array *array);

// Print itinéraire_array
void print_itineraire_array(itineraire_array *array);
#endif
