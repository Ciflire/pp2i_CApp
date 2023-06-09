#include "../include/horaire.h"

horaire *horaire_create(void) {
  horaire *h = (horaire *)malloc(sizeof(horaire));
  h->heure_depart = 0;
  h->heure_arrivee = 0;
  return h;
}

void horaire_destroy(horaire *h) { free(h); }

int horaire_getDepart(horaire *h) { return h->heure_depart; }

int horaire_getArrivee(horaire *h) { return h->heure_arrivee; }

void horaire_setDepart(horaire *h, int heure_depart) {
  h->heure_depart = heure_depart;
}

void horaire_setArrivee(horaire *h, int heure_arrivee) {
  h->heure_arrivee = heure_arrivee;
}

void horaire_print(horaire *h) {
  printf("Horaire: %d - %d\n", h->heure_depart, h->heure_arrivee);
}
