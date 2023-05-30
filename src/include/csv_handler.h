#include "bornes_graph.h"
#include "vehicule_list.h"
#include <string.h>

#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#define NB_BORNES 3858

bornes_graph *generate_graph_fromCSV(int autonomie, bornes_list *list_de_toutes_les_bornes, int *distances);
int index_of_distance(int a, int b);
void getBornesNumberFromIndex(int indexdistance, int *idborne1, int *idborne2);
void generateListFromCSV(char *csvLine, int *resultList, int *resultSize,
                         int autonomie);
void getCarInfos(vehicule_list *v_list);

#endif
