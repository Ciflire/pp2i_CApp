#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __HORAIRE_H__
#define __HORAIRE_H__

// Define a structure for a horaire
struct horaire {
  int departureTime;
  int arrivalTime;
};

// Define the type horaire containing all data about an horaire
typedef struct horaire horaire;

// Creates a new horaire
horaire *horaire_create(void);

// Creates a new horaire with values
horaire *horaire_createWithValues(int arrivalTime, int dpartureTime);

// Destroys an horaire
void horaire_destroy(horaire *h);

// Get the departure time stored in horaire
int horaire_getDepart(horaire *h);

// Get the arrival time stored in horaire
int horaire_getArrivee(horaire *h);

// Set the departure time stored in horaire
void horaire_setDepart(horaire *h, int departureTime);

// Set the arrival time stored in horaire
void horaire_setArrivee(horaire *h, int arrivalTime);

// Prints an horaire
void horaire_print(horaire *h);

#endif
