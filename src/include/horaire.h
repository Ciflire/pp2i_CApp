#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __HORAIRE_H__
#define __HORAIRE_H__

struct horaire {
  int departureTime;
  int arrivalTime;
};

typedef struct horaire horaire;

horaire *horaire_create(void);

horaire *horaire_createWithValues(int departureTime, int arrivalTime);

void horaire_destroy(horaire *h);

int horaire_getDepart(horaire *h);

int horaire_getArrivee(horaire *h);

void horaire_setDepart(horaire *h, int departureTime);

void horaire_setArrivee(horaire *h, int arrivalTime);

void horaire_print(horaire *h);

#endif
