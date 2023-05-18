#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BORNE_H
#define BORNE_H

struct borne {
  int id;
  double xpos;
  double ypos;
  double power;
  int qte;
};

typedef struct borne borne;
<<<<<<< Updated upstream

borne *create_borne(int id, double xpos, double ypos, double power, int qte);

void destroy_borne(borne *b);
=======
>>>>>>> Stashed changes

#endif
