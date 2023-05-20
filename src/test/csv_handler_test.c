#include "../include/bornes_graph.h"
#include "../include/csv_handler.h"

int main(void) {
  printf("Hello world\n");
  bornes_list *list_de_toutes_les_bornes = create_bornes_list();
  int *distances = (int *)malloc(sizeof(int) * 184099266);
  bornes_graph *bg = generate_graph_fromCSV(150,list_de_toutes_les_bornes, distances);
  if (bg == NULL) {
    printf("Error while generating graph\n");
    return 1;
  }
  printf("Graph generated\n");
  destroy_bornes_graph(bg);
  printf("Graph destroyed\n");
  vehicule_list* v = create_vehicule_list();
  getCarInfos(v);
  printf("Car infos got\n");
  destroy_vehicule_list(v);
  return 0;
}
