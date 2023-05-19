#include "../include/bornes_list.h"

int main(void) {
  bornes_list *bl = create_bornes_list();
  add_borne(bl, create_borne(1, 1.0, 1.0, 1.0, 1));
  add_borne(bl, create_borne(2, 2.0, 2.0, 2.0, 2));
  add_borne(bl, create_borne(3, 3.0, 3.0, 3.0, 3));
  add_borne(bl, create_borne(4, 4.0, 4.0, 4.0, 4));
  add_borne(bl, create_borne(5, 5.0, 5.0, 5.0, 5));
  add_borne(bl, create_borne(6, 6.0, 6.0, 6.0, 6));
  add_borne(bl, create_borne(7, 7.0, 7.0, 7.0, 7));
  add_borne(bl, create_borne(8, 8.0, 8.0, 8.0, 8));
  add_borne(bl, create_borne(9, 9.0, 9.0, 9.0, 9));
  add_borne(bl, create_borne(10, 10.0, 10.0, 10.0, 10));
  add_borne(bl, create_borne(11, 11.0, 11.0, 11.0, 11));
  add_borne(bl, create_borne(12, 12.0, 12.0, 12.0, 12));
  printf("%i\n", get_length(bl));
  destroy_bornes_list(bl);
}
