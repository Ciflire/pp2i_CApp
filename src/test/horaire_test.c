#include "../include/horaire.h"

int main(void) {
  horaire *h1 = horaire_create();
  h1->heure_depart = 1;
  h1->heure_arrivee = 2;

  horaire *h2 = horaire_create();
  h2->heure_depart = 3;
  h2->heure_arrivee = 4;

  horaire *h3 = horaire_create();
  h3->heure_depart = 134;
  h3->heure_arrivee = 2398;

  horaire_print(h1);
  horaire_print(h2);
  horaire_print(h3);

  horaire_destroy(h1);
  horaire_destroy(h2);
  horaire_destroy(h3);

  return 0;
}
