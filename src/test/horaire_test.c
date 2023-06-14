#include "../include/horaire.h"

int main(void) {
  horaire *h1 = horaire_create();
  h1->departureTime = 1;
  h1->arrivalTime = 2;

  horaire *h2 = horaire_create();
  h2->departureTime = 3;
  h2->arrivalTime = 4;

  horaire *h3 = horaire_create();
  h3->departureTime = 134;
  h3->arrivalTime = 2398;

  horaire_print(h1);
  horaire_print(h2);
  horaire_print(h3);

  horaire_destroy(h1);
  horaire_destroy(h2);
  horaire_destroy(h3);

  return 0;
}
