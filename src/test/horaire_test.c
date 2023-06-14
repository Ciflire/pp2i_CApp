#include "../include/horaire.h"
#include <assert.h>

int main(void) {
  // Testing horaire_create
  horaire *h1 = horaire_create();
  h1->departureTime = 1;
  h1->arrivalTime = 2;

  horaire *h2 = horaire_create();
  h2->departureTime = 3;
  h2->arrivalTime = 4;

  horaire *h3 = horaire_create();
  h3->departureTime = 134;
  h3->arrivalTime = 2398;

  printf("    [Debug horaire] : Test horaire_create passed\n");

  // Testing horaire_createWithValues

  horaire *h4 = horaire_createWithValues(1, 2);

  printf("    [Debug horaire] : Test horaire_createWithValues passed\n");

  // Testing horaire_getDepart

  assert(horaire_getDepart(h1) == 1);
  assert(horaire_getDepart(h2) == 3);
  assert(horaire_getDepart(h3) == 134);

  printf("    [Debug horaire] : Test horaire_getDepart passed\n");

  // Testing horaire_getArrivee

  assert(horaire_getArrivee(h1) == 2);
  assert(horaire_getArrivee(h2) == 4);
  assert(horaire_getArrivee(h3) == 2398);

  printf("    [Debug horaire] : Test horaire_getArrivee passed\n");

  // Testing horaire_print
  horaire_print(h1);
  horaire_print(h2);
  horaire_print(h3);

  printf("    [Debug horaire] : Test horaire_print passed\n");

  // Testing horaire_destroy
  horaire_destroy(h1);
  horaire_destroy(h2);
  horaire_destroy(h3);

  printf("    [Debug horaire] : Test horaire_destroy passed\n");
  return 0;
}
