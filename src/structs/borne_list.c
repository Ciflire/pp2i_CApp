#include "../include/borne_list.h"


borne_list *borne_list_create(void) {
  borne_list *list = malloc(sizeof(borne_list));
  list->prev = list;
  list->next = list;
  list->borne = NULL;
  list->index = 0;
  return list;
}

borne_list *borne_list_getNext(borne_list *list) { return list->next; }

borne *borne_list_getBorne(borne_list *list) { return list->borne; }

void borne_list_destroy(borne_list *list) {
  borne_list *temp = list->next;
  if (borne_list_length(list->prev) == 0) {
    free(list);
    return;
  }
  for (int i = 1; i < borne_list_length(list); i++) {
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

borne* borne_list_getBorneById(borne_list *list, int id) {
  if (borne_list_length(list) == 0) {
    return NULL;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    if (temp->borne->id == id) {
      return borne_list_getBorne(temp);
    }
    temp = temp->next;
  }
  return NULL;
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

void borne_list_printPathLink(borne_list* list){
  char* url = "https://www.google.com/maps/dir/";
  if (borne_list_length(list) == 0) {
    printf("Liste vide\n");
    return;
  }
  borne_list *temp = list;
  printf("%s", url);
  for (int i = 0; i < borne_list_length(list); i++) {
    printf("'%lf,%lf'/", temp->borne->latitude, temp->borne->longitude);
    temp = temp->next;
  }
  printf("\n");
}
  
