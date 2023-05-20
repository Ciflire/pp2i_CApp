#include "../include/vehicule_list.h"

int main(void) {
  vehicule_list *vl = create_vehicule_list();
  for (int i=0; i<100; i++) {
    vehicule *v = create_vehicule(i, "test", 2, 3);
    add_vehicule(vl, v);
  }
  //vehicule *v = create_vehicule(1, "test", 2, 3);
  //add_vehicule(vl, v);
  destroy_vehicule_list(vl);
  return 0;
}
