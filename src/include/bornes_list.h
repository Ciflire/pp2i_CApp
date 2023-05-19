#include "borne.h"

#ifndef BORNES_LIST_H
#define BORNES_LIST_H

struct bornes_list {
  int index;
  borne *borne;
  struct bornes_list *next;
  struct bornes_list *prev;
};

typedef struct bornes_list bornes_list;

// Construct a bornes_list
bornes_list *create_bornes_list(void);

// Destroy a bornes_list
void destroy_bornes_list(bornes_list *bl);

// Add a borne to a bornes_list
void add_borne(bornes_list *bl, borne *b);

// Get a borne at a given index
borne *get_borne(bornes_list *bl, int index);

// Get the length of a bornes_list
int get_length(bornes_list *bl);

bool is_borne_in_list(bornes_list *bl, int id);

borne *get_borne_by_id(bornes_list *bl, int id);

void print_bornes_list(bornes_list *bl);

#endif
