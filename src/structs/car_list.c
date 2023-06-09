#include "../include/car_list.h"

car_list *car_list_create(void) {
  car_list *list = malloc(sizeof(car_list));
  list->prev = list;
  list->next = list;
  list->car = NULL;
  list->index = 0;
  return list;
}

car *car_list_getCar(car_list *list) { return list->car; }

void car_list_destroy(car_list *list) {
  car_list *temp = list->next;
  if (car_list_length(list->prev) == 0) {
    free(list);
    return;
  }
  for (int i = 1; i < car_list_length(list); i++) {
    temp = temp->next;
    car_destroy(temp->prev->car);
    free(temp->prev);
  }
  car_destroy(temp->car);
  free(temp);
  return;
}

int car_list_length(car_list *list) { return list->prev->index; }

bool car_list_iscarInList(car_list *list, car *car) {
  if (car_list_length(list) == 0) {
    return false;
  }
  car_list *temp = list;
  for (int i = 0; i < car_list_length(list); i++) {
    if (car_equals(temp->car, car)) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void car_list_append(car_list *list, car *car) {
  if (car_list_length(list) == 0) {
    list->car = car;
    list->index = 1;
    return;
  }
  car_list *b_l_new = malloc(sizeof(car_list));
  b_l_new->car = car;
  b_l_new->next = list;
  b_l_new->prev = list->prev;
  list->prev = b_l_new;
  b_l_new->prev->next = b_l_new;
  b_l_new->index = b_l_new->prev->index + 1;
  return;
}

car *car_list_getCarById(car_list *list, int id) {
  if (car_list_length(list) == 0) {
    return NULL;
  }
  car_list *temp = list;
  for (int i = 0; i < car_list_length(list); i++) {
    if (temp->car->id == id) {
      return car_list_getCar(temp);
    }
    temp = temp->next;
  }
  return NULL;
}

void car_list_print(car_list *list) {
  if (car_list_length(list) == 0) {
    printf("Liste vide\n");
    return;
  }
  car_list *temp = list;
  for (int i = 0; i < car_list_length(list); i++) {
    printf("car %d :\n", temp->index);
    car_print(temp->car);
    temp = temp->next;
  }
  return;
}
