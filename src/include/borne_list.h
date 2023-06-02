#include "borne.h"

#ifndef BORNE_LIST_H
#define BORNE_LIST_H

struct borne_list {
  int index;
  borne *borne;
  struct borne_list *next;
  struct borne_list *prev;
};

typedef struct borne_list borne_list;

// Creates a list of bornes
borne_list *borne_list_create(borne *borne);

// Destroys a list of bornes
void borne_list_destroy(borne_list *list);

// Get the index of a borne in a list
int borne_list_getIndex(borne_list *list);

// Returns the borne of the link
borne *borne_list_getBorne(borne_list *list);

// Get the next borne in a list
borne_list *borne_list_getNext(borne_list *list);

// Get the previous borne in a list
borne_list *borne_list_getPrev(borne_list *list);

// Appends a borne to a list of bornes
void borne_list_append(borne_list *list, borne *borne);

// Get the length of a list of bornes
int borne_list_length(borne_list *list);

// Check if borne is in list
int borne_list_isBorneInList(borne_list *list, borne *borne);

#endif