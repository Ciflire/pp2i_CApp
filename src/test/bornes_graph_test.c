#include "../include/bornes_graph.h"

int main(void) {
  bornes_graph *bg = create_bornes_graph(50000);
  for (int i = 0; i < 10000000; i++)
  {
    add_borne_index(bg, i%49999, create_borne(i, i, i, i, i));
  }
  
 
  destroy_bornes_graph(bg);
  return 0;
}
