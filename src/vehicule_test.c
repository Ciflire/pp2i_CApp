#include "vehicule.h"

int main(void) {
  vehicule *v = create_vehicule(1, "test", 2);
  destroy_vehicule(v);
  return 0;
}
