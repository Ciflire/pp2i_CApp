#include "include/itineraire_array.h"
#include "include/bornes_list.h"

//Note, hours are initally set to -1
itineraire_array *itineraire_array_new(int size){
  itineraire_array *array = malloc(sizeof(itineraire_array));
  array->size = size;
  array->array = calloc(size, sizeof(itineraire));
  for (int i = 0; i < size; i++) {
    array->array[i]->horaires = horaire_list_new(-1);
    array->array[i]->chemin = create_bornes_list();
  }
  return array;
}

void destroy_itineraire_array(itineraire_array *array){
  for (int i = 0; i < array->size; i++) {
    destroy_horaire_list(array->array[i]->horaires);
    destroy_bornes_list(array->array[i]->chemin);
    free(array->array[i]);
  }
  free(array->array);
  free(array);
}

void print_itineraire_array(itineraire_array *array){
  for (int i = 0; i < array->size; i++) {
    printf("Itineraire %d\n", i);
    print_horaire_list(array->array[i]->horaires);
    print_bornes_list(array->array[i]->chemin);
  }
}