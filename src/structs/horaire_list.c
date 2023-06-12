#include "../include/horaire_list.h"

// Creates a new list of horaires
horaire_list *horaire_list_create(void) {
  horaire_list *list = (horaire_list *)malloc(sizeof(horaire_list));
  list->horaire = NULL;
  list->next = list;
  list->prev = list;
  return list;
}

// Destroys a list of horaires
void horaire_list_destroy(horaire_list *list) {
  horaire_list *temp = list->next;
  if (horaire_list_length(list->prev) == 0) {
    free(list);
    return;
  }
  for (int i = 1; i < horaire_list_length(list); i++) {
    temp = temp->next;
    horaire_destroy(temp->prev->horaire);
    free(temp->prev);
  }
  horaire_destroy(temp->horaire);
  free(temp);
  return;
}

// Get the index of a horaire in a list
int horaire_list_getIndex(horaire_list *list) { return list->index; }

// Returns the horaire of the link
horaire *horaire_list_gethoraire(horaire_list *list) { return list->horaire; }

// Get the next horaire in a list
horaire_list *horaire_list_getNext(horaire_list *list) { return list->next; }

// Get the previous horaire in a list
horaire_list *horaire_list_getPrev(horaire_list *list) { return list->prev; }

// Appends a horaire to a list of horaires
void horaire_list_append(horaire_list *list, horaire *horaire) {
  horaire_list *new_horaire = horaire_list_create();
  new_horaire->horaire = horaire;
  new_horaire->index = horaire_list_length(list) + 1;
  new_horaire->prev = list->prev;
  new_horaire->next = list;
  list->prev->next = new_horaire;
  list->prev = new_horaire;
}

// Inserts a horaire in a list of horaires
void horaire_list_insert(horaire_list *list, horaire *horaire) {
  horaire_list *current = list;
  bool beenInserted = false;
  for (int i = 0; i < horaire_list_length(list); i++) {
    if (current->horaire->heure_depart < horaire->heure_arrivee &&
        !(beenInserted)) {
      horaire_list_append(current, horaire);
      beenInserted = true;
    }
    if (beenInserted) {
      current->index = current->index + 1;
    }
    current = current->next;
  }
}

// Get the length of a list of horaires
int horaire_list_length(horaire_list *list) { return list->prev->index; }

// Prints a list of horaires
void horaire_list_print(horaire_list *list) {
  if (horaire_list_length(list) == 0) {
    printf("Liste vide\n");
    return;
  }
  horaire_list *current = list->next;
  while (current != list) {
    printf("Horaire %d: %d - %d\n", current->index,
           horaire_getDepart(current->horaire),
           horaire_getArrivee(current->horaire));
    current = current->next;
  }
}
