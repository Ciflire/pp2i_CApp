#include "../include/bornes_graph.h"

int main(void) {
  bornes_graph *bg = create_bornes_graph(5);
  for (int i = 0; i < 1000; i++)
  {
    add_borne_index(bg, i%2, create_borne(i, i, i, i, i));
  }
  
 
  destroy_bornes_graph(bg);
  return 0;
}
