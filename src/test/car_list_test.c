#include "../include/car_list.h"
#include <time.h>
#include "../include/timer.h"
#include <assert.h>

int main(void) {
  // Testing car_list_append
  for (int i = 1; i < 5; i++) {
    
    timer_start();
    car_list *list = car_list_create();
    for (int j = 0; j < (1000000 * i); j++) {
      car *b = car_create("Balek", j, 1.0, 1.0);
      car_list_append(list, b);
    }
    printf("    [Debug car_list] : Test car_list_append %d passed\n",i);

    timer_stop();
    timer_print();
    // Testing car_list_length
    assert(car_list_length(list) == (1000000 * i));

    printf("    [Debug car_list] : Test car_list_length %d passed\n",i);

    // Testing car_list_destroy 
    car_list_destroy(list);

    printf("    [Debug car_list] : Test car_list_destroy %d passed\n",i);
  }
  return 0;
}
