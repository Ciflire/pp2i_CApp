#include "include/horaire.h"

horaire_list* horaire_list_create() {
    horaire_list* list = malloc(sizeof(horaire_list));
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
        horaire_list* current = list;
        list = list->next;
        free(list);
    }
  return;
}

//Warning, adds an hour and not a horaire
void add_horaire(horaire_list *list, int heure){
    horaire_list* new = malloc(sizeof(horaire_list));
    new->heure = heure;
    new->next = NULL;
    new->prev = NULL;
    if (list->index == -1) {
        list->next = new;
        list->prev = new;
        list->index = 1;
        return;
    }
    horaire_list* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
    new->prev = current;
    list->index++;
    return;
}

int get_horaire_list_size(horaire_list *list){
  if(list->index == -1){
    return 0;
  } else {
    return list->prev->index;
  }
}

void print_horaire_list(horaire_list *list){
  if (list->index == -1) {
    printf("Liste vide\n");
    return;
  } else {
    horaire_list* current = list;
    for (int i=0; i < get_horaire_list_size(list); i++) {
      printf("%d\n", current->heure);
      current = current->next;
    }
  }
}