#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999
#define MAX 20000
#include "csv_handler.h"

void Dijkstra(float *longeurs, int n, int start, int end, float autonomy) {

  if (longeurs[index_of_distance(start,end)] < autonomy) {
    printf("Vous pouvez aller directement à votre destination\n");
    return;
  } else {
    printf("Vous ne pouvez pas aller directement à votre destination\n");
    return;
  }
}

int main() {
  borne_t bornes[MAX];
  csv_bornes(bornes);
    
  float *longeurs =(float *)malloc(sizeof(float)*184099266);
  csv_adjacence(longeurs);
  
  printf("%f\n",bornes[0].X);

  printf("%f\n",longeurs[index_of_distance(0,100)]);
  Dijkstra(longeurs, 20000, 0, 100, 680.0);
  printf("%f\n",longeurs[index_of_distance(0,15000)]);
  Dijkstra(longeurs, 20000, 0, 15000, 680.0);

  return 0;
}