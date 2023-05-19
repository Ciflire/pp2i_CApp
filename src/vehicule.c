#include "include/vehicule.h"

vehicule *create_vehicule(int id, char *name, int autonomie) {
  vehicule *v = malloc(sizeof(vehicule));
  v->id = id;
  v->name = name;
  v->autonomie = autonomie;
  return v;
}

void destroy_vehicule(vehicule *v) { free(v); }
