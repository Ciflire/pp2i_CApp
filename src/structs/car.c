#include "../include/car.h"

// Creates a new car
car *car_create(char *model, int id, int autonomy, double powerCapacity){
    car *c = malloc(sizeof(car));
    c->model = model;
    c->id = id;
    c->autonomyMax = autonomy;
    c->autonomyUsable = autonomy;
    c->autonomyAct = autonomy;
    c->capacity = powerCapacity;
    return c;
}

// Destroys a car
void car_destroy(car *c){free(c);}

// Returns the model of a car
char *car_getModel(car *c){return c->model;}

// Returns the id of a car
int car_getId(car *c){return c->id;}

// Returns the autonomy of a car
int car_getAutonomyMax(car *c) { return c->autonomyMax; }

// Returns the power capacity of a car
double car_getPowerCapacity(car *c) { return c->capacity; }

// Check if two cars are equal
bool car_equals(car *c1, car *c2){
    return c1->id == c2->id && c1->autonomyMax == c2->autonomyMax &&
           c1->capacity == c2->capacity;
    }

// Print car information
void car_print(car *c){
    printf("Car %d, Model: %s, AutonomyMax: %d, Usable autonomy: %lf, Rn "
           "autonomy: %lf Power Capacity: %f\n",
           c->id, c->model, c->autonomyMax, c->autonomyUsable, c->autonomyAct,
           c->capacity);
    return;
    }
