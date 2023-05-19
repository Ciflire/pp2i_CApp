#include "../include/bornes_graph.h"

int main(void) {
  bornes_graph *bg = create_bornes_graph(5);
  destroy_bornes_graph(bg);
  return 0;
}
