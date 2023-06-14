#include "../include/horaire_list.h"
#include "../include/timer.h"
#include <time.h>

int main(void) {

  // for (int i = 1; i < 10; i++) {
  //   timer_start();
  //   horaire_list *list = horaire_list_create();
  //   for (int j = 0; j < (1000000 * i); j++) {
  //     horaire *b = horaire_create();
  //     b->departureTime = j;
  //     b->arrivalTime = j + 1;

  //     horaire_list_append(list, b);
  //   }
  //   timer_stop();
  //   timer_print();
  //   horaire_list_destroy(list);
  // }
  horaire_list *list = horaire_list_create();
  for (int i = 0; i < 100000; i++) {
    horaire *b = horaire_createWithValues(i, i + 1);
    horaire_list_append(list, b);
  }
  printf("%d\n", horaire_list_length(list));
  horaire_list_destroy(list);

  return 0;
}
// (horaire_list *)
