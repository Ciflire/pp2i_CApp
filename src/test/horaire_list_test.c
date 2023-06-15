#include "../include/horaire_list.h"
#include "../include/timer.h"
#include <stdio.h>
#include <time.h>

int main(void) {

  horaire_list *list = horaire_list_create();
  horaire_list_print(list);

  for (int i = 0; i < 1000; i++) {
    horaire *a = horaire_createWithValues(i, i + 1);
    horaire_list_insert(list, a);
    // horaire_list_print(list);
  }

  horaire_list_print(list);
  horaire_list_destroy(list);
  return 0;
}
