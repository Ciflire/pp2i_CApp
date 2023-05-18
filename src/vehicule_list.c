#include "vehicule_list.h"

vehicule_list *create_vehicule_list(void) {
  vehicule_list *vl = malloc(sizeof(vehicule_list));
  vl->size = 0;
  vl->vehicule = NULL;
  vl->next = NULL;
  return vl;
}

void destroy_vehicule_list(vehicule_list *vl) {
  if (vl->next != NULL) {
    destroy_vehicule_list(vl->next);
  }
  free(vl);
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
