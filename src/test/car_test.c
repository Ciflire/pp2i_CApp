#include "../include/car.h"
#include <assert.h>

int main(void) {
  // Testing car_create
  car *b = car_create("Volvo", 1, 3.0, 4.0);
  car *b1 = car_create("Volvo", 1, 3.0, 4.0);
  car *b2 = car_create("Opel", 2, 3.0, 4.0);
  car *b3 = car_create("Audi", 3, 5.0, 1.2);

  printf("    [Debug car] : Test car_create passed\n");

  // Testing car_print
  car_print(b);
  car_print(b1);
  car_print(b2);
  car_print(b3);

  printf("    [Debug car] : Test car_print passed\n");

  // Testing car_equals
  assert(!car_equals(b, b2));
  assert(!car_equals(b, b3));
  assert(car_equals(b, b1));

  printf("    [Debug car] : Test car_equals passed\n");

  // Testing car_destroy
  car_destroy(b1);
  car_destroy(b2);
  car_destroy(b3);
  car_destroy(b);

  printf("    [Debug car] : Test car_destroy passed\n");
  return 0;
}
