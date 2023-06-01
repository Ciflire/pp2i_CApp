/*
Contient un chemin (liste chainée de bornes),
Contient liste chainée d'horaires
*/

#include "bornes_list.h"
#include "horaire.h"

#ifndef ITINERAIRE_H

#define ITINERAIRE_H

// store both elements in separate variables to
// make it easier to code

// This struc only exists only to simplify the code
struct itineraire {
  horaire_list *horaires;
  bornes_list *chemin;
};

typedef struct itineraire itineraire;

#endif
