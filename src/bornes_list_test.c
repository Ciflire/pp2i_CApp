#include "bornes_list.h"

int main(void) {
  // test every function once
  bornes_list *bl = create_bornes_list();
  borne *b = create_borne(1, 2.0, 3.0, 4.0, 5);
  add_borne(bl, b);
  destroy_bornes_list(bl);
  return 0;
}
