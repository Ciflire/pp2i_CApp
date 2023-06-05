#include "../include/borne.h"


int main() {
  borne *b = borne_create(1, 2, 25, 3.0, 4.0);
  borne *b2 = borne_create(2, 2, 25, 3.0, 4.0);
  borne *b3 = borne_create(3, 2, 55, 5.0, 1.2);

  printf("Creating borne 1, 2 and 3\n");
  borne_print(b);
  borne_print(b2);
  borne_print(b3);

  printf("b == b2 ? %d\n", borne_equals(b, b2));
  printf("b == b3 ? %d\n", borne_equals(b, b3));

  borne_destroy(b);
  borne_destroy(b2);
  borne_destroy(b3);

  return 0;
}
