#include "../include/horaire.h"

horaire *horaire_create(void) {
  horaire *h = (horaire *)malloc(sizeof(horaire));
  h->departureTime = 0;
  h->arrivalTime = 0;
  return h;
}

horaire *horaire_createWithValues(int departureTime, int arrivalTime) {
  horaire *h = (horaire *)malloc(sizeof(horaire));
  h->departureTime = departureTime;
  h->arrivalTime = arrivalTime;
  return h;
}

void horaire_destroy(horaire *h) { free(h); }

int horaire_getDepart(horaire *h) { return h->departureTime; }

int horaire_getArrivee(horaire *h) { return h->arrivalTime; }

void horaire_setDepart(horaire *h, int departureTime) {
  h->departureTime = departureTime;
}

void horaire_setArrivee(horaire *h, int arrivalTime) {
  h->arrivalTime = arrivalTime;
}

void horaire_print(horaire *h) {
  printf("Horaire: %d - %d\n", h->departureTime, h->arrivalTime);
}
