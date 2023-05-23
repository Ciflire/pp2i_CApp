#include "include/borne.h"

// Creates a borne with the given parameters
borne *create_borne(int id, double xpos, double ypos, double power, int qte) {
  borne *b = malloc(sizeof(borne));
  b->id = id;
  b->xpos = xpos;
  b->ypos = ypos;
  b->power = power;
  b->qte = qte;
  return b;
}

// Destroys a borne
void destroy_borne(borne *b) { free(b); }

// Prints a borne to the standard output
void print_borne(borne *b) {
  printf("Borne %d: (%lf, %lf) - %lf - %d\n", b->id, b->xpos, b->ypos, b->power,
         b->qte);
}

// copies a borne
borne *copy_borne(borne *b) {
  return create_borne(b->id, b->xpos, b->ypos, b->power, b->qte);
}
