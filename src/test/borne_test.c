#include "../include/borne.h"

int main(void) {
  borne *b = create_borne(1, 2.0, 3.0, 4.0, 5);
  destroy_borne(b);
  return 0;
}
