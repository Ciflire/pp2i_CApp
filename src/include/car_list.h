#include "car.h"

#ifndef CAR_LIST_H
#define CAR_LIST_H

struct car_list {
  int index;
  car *car;
  struct car_list *next;
  struct car_list *prev;
};

typedef struct car_list car_list;

// Creates a list of cars
car_list *car_list_create(void);

// Destroys a list of cars
void car_list_destroy(car_list *list);

// Get the index of a car in a list
int car_list_getIndex(car_list *list);

// Returns the car of the link
car *car_list_getCar(car_list *list);

// Get the next car in a list
car_list *car_list_getNext(car_list *list);

// Get the previous car in a list
car_list *car_list_getPrev(car_list *list);

// Appends a car to a list of cars
void car_list_append(car_list *list, car *car);

// Get the length of a list of cars
int car_list_length(car_list *list);

// Check if car is in list
int car_list_iscarInList(car_list *list, car *car);

// Print list of cars
void car_list_print(car_list *list);

#endif
