#include "vehicule.h"

#ifndef VEHICULE_LIST_H
#define VEHICULE_LIST_H

struct vehicule_list {
  int size;
  vehicule *vehicule;
  struct vehicule_list *next;
};

typedef struct vehicule_list vehicule_list;

vehicule_list *create_vehicule_list(void);

void destroy_vehicule_list(vehicule_list *vl);

void add_vehicule(vehicule_list *vl, vehicule *v);

int get_vehicule_id_by_name(vehicule_list *vl, char *name);

vehicule *get_vehicule_by_id(vehicule_list *vl, int id);

void print_vehicule_list(vehicule_list *vl);

#endif
