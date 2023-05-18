#include "csv_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borne.h"

#define MAXBORNES 20000

int generate_graph_framCSV (borne_t bornes[]) {
    FILE* fp;
    char row[50];
    char* token = (char*)malloc(50);
    int i = 0;
    
    fp = fopen("data/bornes.csv","r");

    if (!fp){
        printf("Can't open file\n");
        return(-1);
    }

    while(!feof(fp)) {
        fgets(row, 50, fp);
        int id;
        double xpos;
        double ypos;
        double power;
        int qte;
        xpos = strtok(row, ",");
        ypos = strtok(NULL, ",");
        power = strtok(NULL, ",");
        qte = strtok(NULL, ",");
        printf("X: %lf Y: %lf Puissance : %lf Nombre de bornes : %d\n", bornes[i].X, bornes[i].Y, bornes[i].puissance, bornes[i].nombre);
        i++;
    }

    fclose(fp);
    return(0);
}


void generateListFromCSV(char* csvLine, int* resultList, int* resultSize) {
    // Initialisation des variables
    int count = 0;
    
    // Découpage de la ligne CSV en tokens
    char* token = strtok((char*)csvLine, ",");
    while (token != NULL) {
        // Conversion du token en entier si possible
        char* endPtr;
        int value = (int)strtol(token, &endPtr, 10);
        
        // Si le token commence par "-", on ajoute la valeur -1 plusieurs fois à la liste
        if (value <= 0) {
            
            int repetitions = abs(value);
            //printf("Repetitions : %d\n", repetitions);
            for (int i = 0; i < repetitions; i++) {
                // Ajout de la valeur -1 à la liste
                resultList[count++] = -1;
            }
        }
        else {
            // Ajout de la valeur entière à la liste
            resultList[count++] = value;
        }
        
        // Passage au token suivant
        token = strtok(NULL, ",");
    }
    free(token);
    


    
    // Affectation des résultats
    *resultSize = count;
}
/*

int main() {
    FILE* fp;
    
    fp = fopen("data/adjacence.csv","r");

    if (!fp){
        printf("Can't open file\n");
        return(-1);
    }
    char* csvLine = (char*)malloc(184099266);
    int *longeurs = (int *)malloc(sizeof(int)*184099266);
    fgets(csvLine, 184099266, fp);
    int resultSize;
    
    generateListFromCSV(csvLine, longeurs, &resultSize);
    
    //printf("Liste générée : ");
    //for (int i = 0; i < resultSize; i++) {
    //    printf("%d ", longeurs[i]);
    //}
    //printf("\n");
    
    
    
    free(longeurs);
    //free(csvLine);
    free(fp);
    
    return 0;
}
*/


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

