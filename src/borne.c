#include "include/borne.h"

// Construct a borne
borne *create_borne(int id, double xpos, double ypos, double power, int qte) {
  borne *b = malloc(sizeof(borne));
  b->id = id;
  b->xpos = xpos;
  b->ypos = ypos;
  b->power = power;
  b->qte = qte;
  return b;
}

// Destroy a borne
void destroy_borne(borne *b) { free(b); }

void print_borne(borne *b) {
  printf("Borne %lf, %lf\n", b->xpos, b->ypos);
  printf("id : %d\n", b->id);
  printf("Borne %d: (%lf, %lf) - %lf - %d\n", b->id, b->xpos, b->ypos, b->power,
         b->qte);
}

borne *copy_borne(borne *b) {
  return create_borne(b->id, b->xpos, b->ypos, b->power, b->qte);
}
