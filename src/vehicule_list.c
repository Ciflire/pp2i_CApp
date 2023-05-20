#include "include/vehicule_list.h"

vehicule_list *create_vehicule_list(void) {
  vehicule_list *vl = malloc(sizeof(vehicule_list));
  vl->size = 0;
  vl->vehicule = NULL;
  vl->next = NULL;
  return vl;
}

void destroy_vehicule_list(vehicule_list *vl) {
  int size = vl->size;
  if (size == 0) {
    free(vl);
    return;
  }
  for(int i=0;i<size;i++) {
    vehicule_list *next = vl->next;
    destroy_vehicule(vl->vehicule);
    free(vl);
    vl = next;
  }
}

void add_vehicule(vehicule_list *vl, vehicule *v) {
  if (vl->vehicule == NULL) {
    vl->vehicule = v;
  } else if (vl->next == NULL) {
    vl->next = create_vehicule_list();
    vl->next->vehicule = v;
  } else {
    add_vehicule(vl->next, v);
  }
  vl->size++;
}

int get_vehicule_id_by_name(vehicule_list *vl, char *name) {
  if(vl->vehicule == NULL) {
    return -1;
  }
  for (int i = 0; i < vl->size; i++) {
    if (strcmp(vl->vehicule->name, name) == 0) {
      return vl->vehicule->id;
    }
    vl = vl->next;
  }
  return -1;
}

vehicule *get_vehicule_by_id(vehicule_list *vl, int id) {
  if(vl->vehicule == NULL) {
    return NULL;
  }
  for (int i = 0; i < vl->size; i++) {
    if (vl->vehicule->id == id) {
      return vl->vehicule;
    }
    vl = vl->next;
  }
  return NULL;
}
