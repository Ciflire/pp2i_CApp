#include "../include/car.h"

int main(void) {
  car *b1 = car_create("Volvo", 1, 3.0, 4.0);
  car *b2 = car_create("Opel", 2, 3.0, 4.0);
  car *b3 = car_create("Audi", 3, 5.0, 1.2);

  printf("Creating car 1, 2 and 3\n");
  car_print(b1);
  car_print(b2);
  car_print(b3);

  printf("b1 == b2 ? %d\n", car_equals(b1, b2));
  printf("b1 == b3 ? %d\n", car_equals(b1, b3));

  car_destroy(b1);
  car_destroy(b2);
  car_destroy(b3);

  return 0;
}
