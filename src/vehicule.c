#include "include/vehicule.h"

// Creates a vehicule
vehicule *create_vehicule(int id, char *name, int autonomie, double capacity) {
  vehicule *v = malloc(sizeof(vehicule));
  v->id = id;
  v->name = name;
  v->autonomie = autonomie;
  v->capacity = capacity;
  return v;
}

// Destroys a vehicule
void destroy_vehicule(vehicule *v) { free(v); }

// Prints a vehicule
void print_vehicule(vehicule *v) {
  printf("id: %d\n", v->id);
  printf("name: %s\n", v->name);
  printf("autonomie: %d\n", v->autonomie);
  printf("capacity: %f\n", v->capacity);
}
