#include "include/bornes_graph.h"

// creates a bornes_graph of size n O(n)
bornes_graph *create_bornes_graph(int n) {
  bornes_graph *bg = malloc(sizeof(bornes_graph));
  bg->size = n;
  bg->bornes_graph = calloc(n, sizeof(bornes_list *));
  for (int i = 0; i < n; i++) {
    bg->bornes_graph[i] = create_bornes_list();
  }
  return bg;
}

// destroys a bornes_graph
void destroy_bornes_graph(bornes_graph *bg) {
  for (int i = 0; i < bg->size; i++) {
    destroy_bornes_list(bg->bornes_graph[i]);
  }
  free(bg->bornes_graph);
  free(bg);
}

// adds a borne to a bornes_graph at a given index
void add_borne_index(bornes_graph *bg, int index, borne *borne) {
  add_borne(bg->bornes_graph[index], borne);
}

// prints a bornes_graph
void print_bornes_graph(bornes_graph *bg) {
  for (int i = 0; i < bg->size; i++) {
    printf("Borne %d:\n", i);
    print_bornes_list(bg->bornes_graph[i]);
  }
}
