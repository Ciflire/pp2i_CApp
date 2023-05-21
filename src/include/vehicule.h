#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VEHICULE_H
#define VEHICULE_H

struct vehicule {
  int id;
  char *name;
  int autonomie;
  double capacity;
};

typedef struct vehicule vehicule;

vehicule *create_vehicule(int id, char *name, int autonomie, double capacity);

void destroy_vehicule(vehicule *v);

void print_vehicule(vehicule *v);
#endif
