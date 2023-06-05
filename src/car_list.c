#include "include/car_list.h"

borne_list *borne_list_create(void) {
  borne_list *list = malloc(sizeof(borne_list));
  list->prev = NULL;
  list->next = NULL;
  list->borne = NULL;
  list->index = 0;
  return list;
}

void borne_list_destroy(borne_list *list) {
  borne_list *temp = list->next;
  if (borne_list_length(list->prev) == 0) {
    free(list);
    return;
  }
  for (int i = 0; i < borne_list_length(list->prev); i++) {
    temp = temp->next;
    borne_destroy(temp->prev->borne);
    free(temp->prev);
  }
  borne_destroy(temp->borne);
  free(temp);
  return;
}

int borne_list_length(borne_list *list) { return list->prev->index; }

bool borne_list_isBorneInList(borne_list *list, borne *borne) {
  if (borne_list_length(list) == 0) {
    return false;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    if (borne_equals(temp->borne, borne)) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void borne_list_append(borne_list *list, borne *borne) {
  if (borne_list_length(list) == 0) {
    list->borne = borne;
    list->index = 1;
    return;
  }
  borne_list *b_l_new = malloc(sizeof(borne_list));
  b_l_new->borne = borne;
  b_l_new->next = list;
  b_l_new->prev = list->prev;
  list->prev = b_l_new;
  b_l_new->prev->next = b_l_new;
  b_l_new->index = b_l_new->prev->index + 1;
  return;
}

void borne_list_print(borne_list *list) {
  if (borne_list_length(list) == 0) {
    printf("Liste vide\n");
    return;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    printf("Borne %d :\n", temp -> index);
    borne_print(temp->borne);
    temp = temp->next;
  }
  return;
}
  
