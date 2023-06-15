#include "../include/horaire.h"

// Creates a new horaire
horaire *horaire_create(void) {
  horaire *h = (horaire *)malloc(sizeof(horaire));
  h->departureTime = 0;
  h->arrivalTime = 0;
  return h;
}

// Creates a new horaire with values
horaire *horaire_createWithValues(int arrivalTime, int departureTime) {
  horaire *h = (horaire *)malloc(sizeof(horaire));
  h->departureTime = departureTime;
  h->arrivalTime = arrivalTime;
  return h;
}

// Destroys a horaire
void horaire_destroy(horaire *h) { free(h); }

// Gets the departure time stored in horaire
int horaire_getDepart(horaire *h) { return h->departureTime; }

// Gets the arrival time stored in horaire
int horaire_getArrivee(horaire *h) { return h->arrivalTime; }

// Sets the departure time stored in horaire
void horaire_setDepart(horaire *h, int departureTime) {
  h->departureTime = departureTime;
}

// Sets the arrival time stored in horaire
void horaire_setArrivee(horaire *h, int arrivalTime) {
  h->arrivalTime = arrivalTime;
}

// Prints a horaire
void horaire_print(horaire *h) {
  printf("Horaire: %d - %d\n", h->arrivalTime, h->departureTime);
}
