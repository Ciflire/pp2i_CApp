#include "bornes_list.h"

#ifndef BORNES_GRAPH_H
#define BORNES_GRAPH_H

struct bornes_graph {
  int size;
  bornes_list *bornes_graph;
};

typedef struct bornes_graph bornes_graph;

bornes_graph *create_bornes_graph(int n);

void destroy_bornes_graph(bornes_graph *bg);

#endif
