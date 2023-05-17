#include "csv_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBORNES 20000

int csv_bornes (borne_t bornes[]) {
    FILE* fp;
    char row[50];
    char* token = (char*)malloc(50);
    int i = 0;
    
    fp = fopen("../utils/bornes/bornes.csv","r");

    if (!fp){
        printf("Can't open file\n");
        return(-1);
    }

    while(!feof(fp)) {
        fgets(row, 50, fp);

        token = strtok(row, ",");
        bornes[i].X = atof(token);
        token = strtok(NULL, ",");
        bornes[i].Y = atof(token);
        token = strtok(NULL, ",");
        bornes[i].puissance = atof(token);
        token = strtok(NULL, ",");
        bornes[i].nombre = atoi(token);
        // printf("X: %lf Y: %lf Puissance : %lf Nombre de bornes : %d\n", bornes[i].X, bornes[i].Y, bornes[i].puissance, bornes[i].nombre);
        i++;
    }

    fclose(fp);
    return(0);
}

int csv_adjacence (float * longeurs) {
    FILE* fp;
    char row[30];
    int i = 0;
    
    fp = fopen("../utils/bornes/adjacence.csv","r");

    if (!fp){
        printf("Can't open file\n");
        return(-1);
    }

    while(!feof(fp)) {
        fgets(row, 30, fp);
        longeurs[i] = atof(row);
        i++;
    }

    fclose(fp);
    return(0);
}

int index_of_distance(int a, int b){
    
    if (a==b){
        return(0);
    }
    if (a<b){
        return(a+b*(b-1)/2);
    }
    if (a>b){
        return(b+a*(a-1)/2);
    }
    return(-1);
}
