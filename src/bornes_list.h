#include "borne.h"

#ifndef BORNES_LIST_H
#define BORNES_LIST_H

struct bornes_list {
  int size;
  borne *borne;
  struct bornes_list *next;
};

typedef struct bornes_list bornes_list;

bornes_list *create_bornes_list(void);

void destroy_bornes_list(bornes_list *bl);

void add_borne(bornes_list *bl, borne *b);

#endif
