#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __HORAIRE_H__
#define __HORAIRE_H__

struct horaire {
  int heure_depart;
  int heure_arrivee;
};

typedef struct horaire horaire;

horaire *horaire_create(void);

horaire *horaire_createWithValues(int heure_depart, int heure_arrivee);

void horaire_destroy(horaire *h);

int horaire_getDepart(horaire *h);

int horaire_getArrivee(horaire *h);

void horaire_setDepart(horaire *h, int heure_depart);

void horaire_setArrivee(horaire *h, int heure_arrivee);

void horaire_print(horaire *h);

#endif
