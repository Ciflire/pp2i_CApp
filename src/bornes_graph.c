#include "include/bornes_graph.h"

bornes_graph *create_bornes_graph(int n) {
  bornes_graph *bg = malloc(sizeof(bornes_graph));
  bg->size = n;
  bg->bornes_graph = calloc(n, sizeof(bornes_list *));
  for (int i = 0; i < n; i++) {
    bg->bornes_graph[i] = create_bornes_list();
  }
  return bg;
}

void destroy_bornes_graph(bornes_graph *bg) {
  for (int i = 0; i < bg->size; i++) {
    if (bg->bornes_graph[i] != NULL) {
      destroy_bornes_list(bg->bornes_graph[i]);
    }
  }
  free(bg->bornes_graph);
  free(bg);
}

void add_borne_index(bornes_graph *bg, int index, borne *borne) {
  add_borne(bg->bornes_graph[index], borne);
}
