#include "borne.h"
#include "bornes_graph.h"
#include "bornes_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#define NB_BORNES 19189

bornes_graph *generate_graph_fromCSV(int autonomie);
int index_of_distance(int a, int b);
void getBornesNumberFromIndex(int indexdistance, int *idborne1, int *idborne2);
void generateListFromCSV(char *csvLine, int *resultList, int *resultSize,
                         int autonomie);

#endif
