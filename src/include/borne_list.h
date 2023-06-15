#include "borne.h"
#include <string.h>

#ifndef BORNE_LIST_H
#define BORNE_LIST_H

// Define a structure for a list of bornes
struct borne_list {
  int index;
  borne *borne;
  struct borne_list *next;
  struct borne_list *prev;
};

// Define the type borne_list : a double linked cyclic list of borne type
typedef struct borne_list borne_list;

// Creates a list of bornes
borne_list *borne_list_create(void);

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
bool borne_list_isBorneInList(borne_list *list, borne *borne);

// Get a borne by its id
borne *borne_list_getBorneById(borne_list *list, int id);

// Prints a list of bornes
void borne_list_print(borne_list *list);

// Prints the URL to display a path in Google Maps
void borne_list_printPathLink(borne_list *list);

// Prints a url to print a path in Maps integrator
void borne_list_printPathMapsIntegrator(borne_list *list);

void borne_list_savePathInPythonListFormat(borne_list *list, char *filename);


#endif
