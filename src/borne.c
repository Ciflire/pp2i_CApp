#include "include/borne.h"

borne *create_borne(int id, double xpos, double ypos, double power, int qte) {
  borne *b = malloc(sizeof(borne));
  b->id = id;
  b->xpos = xpos;
  b->ypos = ypos;
  b->power = power;
  b->qte = qte;
  return b;
}

void destroy_borne(borne *b) { free(b); }
