#include "../include/car_list.h"

// Creates a car_list
car_list *car_list_create(void) {
  car_list *list = malloc(sizeof(car_list));
  list->prev = list;
  list->next = list;
  list->car = NULL;
  list->index = 0;
  return list;
}

// Destroys a car_list
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

// Get the index of a car in a list
int car_list_getIndex(car_list *list) { return list->index; }

//Returns the car in a list
car *car_list_getCar(car_list *list) { return list->car; }

// Gets the next car_list
car_list *car_list_getNext(car_list *list) { return list->next; }

// Gets the previous car_list
car_list *car_list_getPrev(car_list *list) { return list->prev; }

// Adds a car to a car_list
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

// Gets the length of a car_list
int car_list_length(car_list *list) { return list->prev->index; }

// Check if a car is in a list
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

// Get a car by its id
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

//Prints a list of cars
void car_list_print(car_list *list) {
  if (car_list_length(list) == 0) {
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
