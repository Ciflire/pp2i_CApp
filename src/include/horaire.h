#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HORAIRE_H

#define HORAIRE_H

struct horaire_list {
  long index;
  int heure_arrivee;
  int heure_depart;
  struct horaire_list *next;
  struct horaire_list *prev;
};

typedef struct horaire_list horaire_list;

// Create a horaire_list
horaire_list *horaire_list_create(void);

// Destroy a horaire_list
void destroy_horaire_list(horaire_list *list);

// Add a horaire to a horaire_list
void add_horaire(horaire_list *list, int heure_arrivee, int heure_depart);

// Get the horaire at index i
horaire_list *get_horaire(horaire_list *list, int i);

// Get the size of a horaire_list
long get_horaire_list_size(horaire_list *list);

// Print a horaire_list
void print_horaire_list(horaire_list *list);

#endif
