#include "include/app.h"

int main(void) {
  printf("Combien voulez vous générer de voitures ?\n");
  int nb_vehicules;
  scanf("%d", &nb_vehicules);
  printf("Quelle seed de rd voulez vous utiliser ?\n");
  unsigned int seed;
  scanf("%u", &seed);



  vehicule_list *list_of_all_vehicules = create_vehicule_list();
  getCarInfos(list_of_all_vehicules);
  if(list_of_all_vehicules == NULL){
    printf("Error while getting car infos\n");
    return 1;
  }

  itineraire_array *itineraires = itineraire_array_new(nb_vehicules);
  if(itineraires == NULL){
    printf("Error while creating itineraires\n");
    return 1;
  }
  printf("generating graph\n");
  bornes_list *list_de_toutes_les_bornes = create_bornes_list();
  int *distances = (int *)malloc(sizeof(int) * 184099266);
  bornes_graph *bg =
      generate_graph_fromCSV(AUTONOMIE_MAX, list_de_toutes_les_bornes, distances);
      if(bg == NULL){
        printf("Error while generating graph\n");
        return 1;
      }
  printf("Graph generated\n");
  
  for (int i=0; i<nb_vehicules; i++){
    int error = path(itineraires, &seed, list_of_all_vehicules, list_de_toutes_les_bornes, bg, &i);
    if (error != 0){
      printf("Error while generating path for path nb %d\n",i);
      return 1;
    }
  }
  print_itineraire_array(itineraires);
  free(distances);
  destroy_bornes_graph(bg);
  destroy_bornes_list(list_de_toutes_les_bornes);
  destroy_vehicule_list(list_of_all_vehicules);
  destroy_itineraire_array(itineraires);

  return 0;
}
