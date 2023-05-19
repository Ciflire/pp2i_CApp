#include "../include/bornes_graph.h"

int main(void) {
  bornes_graph *bg = create_bornes_graph(5);
  add_borne_index(bg, 0, create_borne(1, 1.0, 1.0, 1.0, 1));
  add_borne_index(bg, 0, create_borne(2, 2.0, 2.0, 2.0, 2));
  add_borne_index(bg, 0, create_borne(3, 3.0, 3.0, 3.0, 3));
  add_borne_index(bg, 0, create_borne(4, 4.0, 4.0, 4.0, 4));
  add_borne_index(bg, 1, create_borne(5, 5.0, 5.0, 5.0, 5));
  add_borne_index(bg, 1, create_borne(6, 6.0, 6.0, 6.0, 6));
  add_borne_index(bg, 1, create_borne(7, 7.0, 7.0, 7.0, 7));
  add_borne_index(bg, 1, create_borne(8, 8.0, 8.0, 8.0, 8));
  add_borne_index(bg, 2, create_borne(9, 9.0, 9.0, 9.0, 9));
  destroy_bornes_graph(bg);
  return 0;
}
