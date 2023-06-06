#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CAR_H
#define CAR_H

struct car {
  char *model;
  int id;
  int autonomy;
  double powerCapacity;
};

typedef struct car car;

// Creates a new car
car *car_create(char *model, int id, int autonomy, double powerCapacity);

// Destroys a car
void car_destroy(car *c);

// Returns the model of a car
char *car_getModel(car *c);

// Returns the id of a car
int car_getId(car *c);

// Returns the autonomy of a car
int car_getAutonomy(car *c);

// Returns the power capacity of a car
double car_getPowerCapacity(car *c);

// Check if two cars are equal
bool car_equals(car *c1, car *c2);

// Print car information
void car_print(car *c);

#endif
