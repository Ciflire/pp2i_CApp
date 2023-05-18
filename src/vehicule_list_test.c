#include "vehicule_list.h"

int main(void) {
  vehicule_list *vl = create_vehicule_list();
  vehicule *v = create_vehicule(1, "test", 2);
  add_vehicule(vl, v);
  destroy_vehicule_list(vl);
  return 0;
}
