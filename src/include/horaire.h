#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HORAIRE_H

#define HORAIRE_H

struct horaire_list {
  int index;
  int heure;
  struct horaire_list *next;
  struct horaire_list *prev;
};

typedef struct horaire_list horaire_list;

// Create a horaire_list
horaire_list *horaire_list_new(int heure);

// Destroy a horaire_list
void destroy_horaire_list(horaire_list *list);

// Add a horaire to a horaire_list
void add_horaire(horaire_list *list, int heure);

// Get the horaire at index i
horaire_list *get_horaire(horaire_list *list, int i);

// Get the size of a horaire_list
int get_horaire_list_size(horaire_list *list);

// Print a horaire_list
void print_horaire_list(horaire_list *list);

#endif