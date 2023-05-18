#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef VEHICULE_H
#define VEHICULE_H

<<<<<<< Updated upstream
struct vehicule {
  int id;
  char *name;
  int autonomie;
};

typedef struct vehicule vehicule;

vehicule *create_vehicule(int id, char *name, int autonomie);

void destroy_vehicule(vehicule *v);
=======
typedef struct vehicule{
    int id;
    char* name;
    int autonomie;
};

typedef struct vehicule vehicule;
>>>>>>> Stashed changes

#endif
