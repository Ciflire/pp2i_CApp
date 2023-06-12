#include "../include/horaire_list.h"
#include "../include/timer.h"
#include <time.h>

int main(void) {

  for (int i = 1; i < 10; i++) {
    timer_start();
    horaire_list *list = horaire_list_create();
    for (int j = 0; j < (1000000 * i); j++) {
      horaire *b = horaire_create();
      b->heure_depart = j;
      b->heure_arrivee = j + 1;

      horaire_list_append(list, b);
    }
    timer_stop();
    timer_print();
    horaire_list_destroy(list);
  }
  return 0;
}
