#include "include/horaire.h"

horaire_list *horaire_list_create(void) {
  horaire_list *list = malloc(sizeof(horaire_list));
  list->next = NULL;
  list->prev = NULL;
  list->index = -1;
  return list;
}

void destroy_horaire_list(horaire_list *list) {
  int length = get_horaire_list_size(list);
  if (length == 0) {
    free(list);
    return;
  }
  for (int i = 0; i < length; i++) {
    horaire_list *current = list;
    list = list->next;
    free(current);
  }
  return;
}

// Warning, adds an hour and not a horaire
void add_horaire(horaire_list *list, int heure_arrivee, int heure_depart) {
  horaire_list *new = malloc(sizeof(horaire_list));
  new->heure_arrivee = heure_arrivee;
  new->heure_depart = heure_depart;
  new->next = NULL;
  new->prev = NULL;
  if (list->index == -1) {
    list->next = new;
    list->prev = new;
    list->index = 1;
    return;
  }
  printf("list size 1: %ld\n", get_horaire_list_size(list));

  new->index = get_horaire_list_size(list) + 1;
  printf("new->index : %ld\n", new->index);
  new->prev = list->prev;
  new->next = list;
  list->prev->next = new;
  list->prev = new;
  printf("list size 2 : %ld\n", get_horaire_list_size(list));
}

horaire_list *get_horaire(horaire_list *list, int i) {
  if (i > get_horaire_list_size(list)) {
    printf("get_horaire_list_size(list) : %ld\n", get_horaire_list_size(list));
    printf("i : %d\n", i);
    printf("Index out of range get horaire\n");
    return NULL;
  }
  horaire_list *current = list;
  for (int j = 0; j < i; j++) {
    current = current->next;
  }
  return current;
}

long get_horaire_list_size(horaire_list *list) {
  if (list->index == -1) {
    return 0;
  } else {
    return list->prev->index;
  }
}

void print_horaire_list(horaire_list *list) {
  if (list->index == -1) {
    printf("Liste vide\n");
    return;
  } else {
    horaire_list *current = list;
    for (int i = 0; i < get_horaire_list_size(list); i++) {
      printf("heurre arrivée : %d\n", current->heure_arrivee);
      printf("heurre départ : %d\n", current->heure_depart);
      current = current->next;
    }
  }
}
