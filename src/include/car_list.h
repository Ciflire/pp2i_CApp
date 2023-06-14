#include "car.h"

#ifndef CAR_LIST_H
#define CAR_LIST_H

// Define a structure for a list of cars
struct car_list {
  int index;
  car *car;
  struct car_list *next;
  struct car_list *prev;
};

// Define the type car_list : a double linked cyclic list of car type
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

// Gets the length of a list of cars
int car_list_length(car_list *list);

// Check if car is in list
bool car_list_iscarInList(car_list *list, car *car);

// Get a car by its id
car *car_list_getCarById(car_list *list, int id);

// Prints list of cars
void car_list_print(car_list *list);

#endif
