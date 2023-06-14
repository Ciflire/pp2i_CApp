#include "../include/borne.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
  // Testing borne_create
  borne *b = borne_create(1, 2, 25, 3.0, 4.0);
  borne *b2 = borne_create(2, 2, 25, 3.0, 4.0);
  borne *b3 = borne_create(3, 2, 55, 5.0, 1.2);
  borne *b1 = borne_create(1, 2, 25, 3.0, 4.0);
  printf("    [Debug borne] : Test borne_create passed\n");

  // Testing borne_print
  borne_print(b);
  borne_print(b1);
  borne_print(b2);
  borne_print(b3);

  printf("    [Debug borne] : Test borne_print passed\n");

  // Testing borne_equals
  assert(!borne_equals(b, b2));
  assert(!borne_equals(b, b3));
  assert(borne_equals(b, b1));

  printf("    [Debug borne] : Test borne_equals passed\n");

  // Testing borne_destroy
  borne_destroy(b);
  borne_destroy(b1);
  borne_destroy(b2);
  borne_destroy(b3);

  printf("    [Debug borne] : Test borne_destroy passed\n");
  return 0;
}
