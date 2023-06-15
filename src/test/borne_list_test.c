#include "../include/borne_list.h"
#include <time.h>
#include "../include/timer.h"
#include <assert.h>

int main(void) {
  // Testing borne_list_append
  for (int i = 1; i < 5; i++) {
    timer_start();
    borne_list *list = borne_list_create();
    for (int j = 0; j < (1000000 * i); j++) {
      borne *b = borne_create(j, 1, 25, 1.0, 1.0);
      borne_list_append(list, b);
    }
    timer_stop();
    timer_print();

    printf("    [Debug borne_list] : Test borne_list_append %d passed\n",i);

    // Testing borne_list_length
    assert(borne_list_length(list) == (1000000 * i));
    horaire_list_insert(list->borne->horairePdc[0], horaire_createWithValues(1, 2));
    printf("    [Debug borne_list] : Test borne_list_length %d passed\n",i);

    // Testing borne_list_destroy
    borne_list_destroy(list);

    printf("    [Debug borne_list] : Test borne_list_destroy %d passed\n",i);
  }
  return 0;
}
