#include "bornes_list.h"

int main(void) {
  bornes_list *bl = create_bornes_list();
  destroy_bornes_list(bl);
  return 0;
}
