#include "../include/borne.h"

borne *b = borne_create(1, 2, 3.0, 4.0);
borne *b2 = borne_create(2, 2, 3.0, 4.0);

int main() {
  printf("Creating borne 1 et 2\n");
  borne_print(b);
  borne_print(b2);
  printf("b == b2 ? %d\n", borne_equals(b, b2));
  borne_delete(b);
  borne_delete(b2);
  return 0;
}