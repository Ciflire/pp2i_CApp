#include "../include/bornes_list.h"

int main(void) {
  bornes_list *bl = create_bornes_list();
  for (int i = 0; i < 1000; i++)
  {
    add_borne(bl, create_borne(i, i, i, i, i));
  }

  for (int i = 1000; i < 2000; i++)
  {
    if (is_borne_in_list(bl, i)){
      printf("%d,%d\n", is_borne_in_list(bl, i),i);
    }
  }
  
  printf("%i\n", get_length(bl));
  destroy_bornes_list(bl);
}
