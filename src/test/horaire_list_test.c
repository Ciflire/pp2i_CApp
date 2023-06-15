#include "../include/horaire_list.h"
#include "../include/timer.h"
#include <stdio.h>
#include <time.h>

int main(void) {

  horaire_list *list = horaire_list_create();
  horaire_list_print(list);
  horaire *a = horaire_createWithValues(1, 2);
  horaire_list_insert(list, a);
  horaire_list_print(list);
  horaire_list_destroy(list);

  return 0;
}
