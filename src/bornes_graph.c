#include "bornes_graph.h"

bornes_graph *create_bornes_graph(int n) {
  bornes_graph *bg = malloc(sizeof(bornes_graph));
  bg->size = n;
  bg->bornes_graph = calloc(n, sizeof(bornes_list));
  for (int i = 0; i < n; i++) {
    bg->bornes_graph[i].size = 0;
    bg->bornes_graph[i].borne = NULL;
    bg->bornes_graph[i].next = NULL;
  }
  return bg;
}

void destroy_bornes_graph(bornes_graph *bg) {
  if (bg != NULL) {
    for (int i = 0; i < bg->size; i++) {
      printf("je rentre dans la boucle\n");
      destroy_bornes_list(bg->bornes_graph[i]);
    }
    if (bg->bornes_graph != NULL) {
      printf("je rentre dans le if\n");
      free(bg->bornes_graph);
    }
    printf("je free le dernier pointer\n");
    free(bg);
  }
}
