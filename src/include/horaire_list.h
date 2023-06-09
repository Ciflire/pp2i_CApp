#include "horaire.h"

#ifndef __HORAIRE_LIST_H__
#define __HORAIRE_LIST_H__

struct horaire_list {
    int index;
    struct horaire_list *next;
    struct horaire_list *prev;
    horaire *horaire;
};

typedef struct horaire_list horaire_list;

// Creates a list of horaires
horaire_list *horaire_list_create(void);

// Destroys a list of horaires
void horaire_list_destroy(horaire_list *list);

// Get the index of a horaire in a list
int horaire_list_getIndex(horaire_list *list);

// Returns the horaire of the link
horaire *horaire_list_gethoraire(horaire_list *list);

// Get the next horaire in a list
horaire_list *horaire_list_getNext(horaire_list *list);

// Get the previous horaire in a list
horaire_list *horaire_list_getPrev(horaire_list *list);

// Appends a horaire to a list of horaires
void horaire_list_append(horaire_list *list, horaire *horaire);

// Insert a horaire in a list of horaires
void horaire_list_insert(horaire_list *list, horaire *horaire);

// Get the length of a list of horaires
int horaire_list_length(horaire_list *list);


// Prints a list of horaires
void horaire_list_print(horaire_list *list);


#endif
