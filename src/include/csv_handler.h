#include "bornes_graph.h"

#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#define NB_BORNES 19188

bornes_graph *generate_graph_fromCSV(int autonomie);
int index_of_distance(int a, int b);
void getBornesNumberFromIndex(int indexdistance, int *idborne1, int *idborne2);
void generateListFromCSV(char *csvLine, int *resultList, int *resultSize,
                         int autonomie);

#endif
