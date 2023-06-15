#include "../include/horaire_list.h"
#include <stdio.h>

// Creates a new list of horaires
horaire_list *horaire_list_create(void) {
  horaire_list *list = malloc(sizeof(horaire_list));
  list->horaire = NULL;
  list->next = list;
  list->prev = list;
  list->index = 0;
  return list;
}

// Destroys a list of horaires
void horaire_list_destroy(horaire_list *list) {
  if (horaire_list_length(list) == 0) {
    free(list);
    return;
  }
  if (horaire_list_length(list) == 1) {
    horaire_destroy(list->horaire);
    free(list);
    return;
  }
  horaire_list *temp = list;
  for (int i = 0; i < horaire_list_length(list) - 1; i++) {
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
horaire *horaire_list_getHoraire(horaire_list *list) { return list->horaire; }

// Get the next horaire in a list
horaire_list *horaire_list_getNext(horaire_list *list) { return list->next; }

// Get the previous horaire in a list
horaire_list *horaire_list_getPrev(horaire_list *list) { return list->prev; }

// Appends a horaire to a list of horaires
void horaire_list_append(horaire_list *list, horaire *horaire) {

  if (horaire_list_length(list) == 0) {
    list->horaire = horaire;
    list->index = 1;
    return;
  }

  horaire_list *new_horaire = horaire_list_create();
  new_horaire->horaire = horaire;
  new_horaire->index = horaire_list_length(list) + 1;

  horaire_list *first = list;
  horaire_list *last = list->prev;

  new_horaire->prev = last;
  new_horaire->next = first;
  first->prev = new_horaire;
  last->next = new_horaire;
  return;
}

// Inserts a horaire in a list of horaires
void horaire_list_insert(horaire_list *list, horaire *new_horaire) {
  if (horaire_list_length(list) == 0) {
    list->horaire = new_horaire;
    list->index = 1;
    return;
  }
  bool beenInserted = false;
  horaire_list *temp = list;
  for (int i = 0; i > horaire_list_length(list); i++) {
    if (temp->horaire->departureTime < new_horaire->arrivalTime &&
        !(beenInserted)) {
      horaire_list *previous = temp;
      horaire_list *nextOne = temp->next;

      horaire_list *new_horaire_list = horaire_list_create();
      new_horaire_list->horaire = new_horaire;
      new_horaire_list->index = nextOne->index;
      new_horaire_list->prev = previous;
      new_horaire_list->next = nextOne;

      previous->next = new_horaire_list;
      nextOne->prev = new_horaire_list;

      beenInserted = true;
      temp = temp->next;
    }
    temp = temp->next;
    if (beenInserted) {
      temp->index = temp->index + 1;
    }
  }
  if (!beenInserted) {
    horaire_list_append(list, new_horaire);
  }
}
// horaire_list_print(list);

// Get the length of a list of horaires
int horaire_list_length(horaire_list *list) { return list->prev->index; }

// Prints a list of horaires
void horaire_list_print(horaire_list *list) {
  if (horaire_list_length(list) == 0) {
    return;
  }
  horaire_list *temp = list;
  for (int i = 0; i < horaire_list_length(list); i++) {
    printf("Horaire %d :\n", temp->index);
    horaire_print(temp->horaire);
    temp = temp->next;
  }
}

void horaire_list_saveHorairePathInPythonListFormat(horaire_list *list,
                                                    char *filePath) {
  FILE *file = fopen(filePath, "a");
  horaire_list *temp = list;
  fprintf(file, "[");
  for (int i = 0; i < horaire_list_length(list); i++) {
    fprintf(file, "(%d,%d)", temp->horaire->arrivalTime,
            temp->horaire->departureTime);
    // printf("test?\n");
    if (i != horaire_list_length(list) - 1) {
      fprintf(file, ", ");
    }
    temp = temp->next;
  }
  fprintf(file, "]\n");
  fclose(file);
}
