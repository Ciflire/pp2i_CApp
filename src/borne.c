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

// Print a borne
void print_borne(borne *b) {
  printf("id: %d, xpos: %f, ypos: %f, power: %f, qte: %d\n", b->id, b->xpos,
         b->ypos, b->power, b->qte);
}