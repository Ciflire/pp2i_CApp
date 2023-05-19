#include "include/bornes_graph.h"

// Construct a bornes_graph with n bornes_list
bornes_graph *create_bornes_graph(int n) {
  bornes_graph *bg = malloc(sizeof(bornes_graph));
  bg->size = n;
  bg->bornes_graph = calloc(n, sizeof(bornes_list *));
  for (int i = 0; i < n; i++) {
    bg->bornes_graph[i] = create_bornes_list();
  }
  return bg;
}

// Destroy a bornes_graph
void destroy_bornes_graph(bornes_graph *bg) {
  for (int i = 0; i < bg->size; i++) {
    if (bg->bornes_graph[i] != NULL) {
      destroy_bornes_list(bg->bornes_graph[i]);
    }
  }
  free(bg->bornes_graph);
  free(bg);
}

// Add a borne to a bornes_graph at a given index
void add_borne_index(bornes_graph *bg, int index, borne *borne) {
  add_borne(bg->bornes_graph[index], borne);
}
