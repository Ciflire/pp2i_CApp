#include "include/csv_handler.h"

bornes_graph *generate_graph_fromCSV(int autonomie) {
  FILE *f_adjacence;
  printf("in generate_graph_fromCSV\n");
  f_adjacence = fopen("data/adjacence.csv", "r");

  if (!f_adjacence) {
    printf("Can't open file adjacence.csv\n");
    return (NULL);
  }
  char *csvLine = (char *)malloc(184099266);
  int *longeurs = (int *)malloc(sizeof(int) * 184099266);
  fgets(csvLine, 184099266, f_adjacence);
  fclose(f_adjacence);
  int resultSize;

  generateListFromCSV(csvLine, longeurs, &resultSize, autonomie);
  printf("resultSize = %d\n", resultSize);
  FILE *fp;
  char row[50];

  fp = fopen("data/bornes.csv", "r");

  if (!fp) {
    printf("Can't open file bornes.csv\n");
    return (NULL);
  }
  bornes_graph *bg = create_bornes_graph(NB_BORNES);
  printf("bg created\n");
  // création de la liste de toutes les bornes

  int id = 0;
  bornes_list *list_de_toutes_les_bornes = create_bornes_list();
  while (!feof(fp)) {
    fgets(row, 40000, fp);
    double xpos;
    double ypos;
    double power;
    int qte;
    xpos = (double)*strtok(row, ",");
    ypos = (double)*strtok(NULL, ",");
    power = (double)*strtok(NULL, ",");
    qte = (int)*strtok(NULL, ",");
    add_borne(list_de_toutes_les_bornes,
              create_borne(id, xpos, ypos, power, qte));
    id++;
  }
  fclose(fp);
  printf("list_de_toutes_les_bornes created\n");
  for (int i = 0; i < resultSize; i++) {
    if (longeurs[i] != -1) {
      int borne1;
      int borne2;
      getBornesNumberFromIndex(i, &borne1, &borne2);

      add_borne(bg->bornes_graph[borne1],
                get_borne(list_de_toutes_les_bornes, borne2));
      add_borne(bg->bornes_graph[borne2],
                get_borne(list_de_toutes_les_bornes, borne1));
    }
  }
  free(longeurs);
  free(csvLine);
  destroy_bornes_list(list_de_toutes_les_bornes);

  return bg;
}

void generateListFromCSV(char *csvLine, int *resultList, int *resultSize,
                         int autonomie) {
  // Initialisation des variables
  int count = 0;

  // Découpage de la ligne CSV en tokens
  char *token = strtok((char *)csvLine, ",");
  while (token != NULL) {
    // Conversion du token en entier si possible
    char *endPtr;
    int value = (int)strtol(token, &endPtr, 10);

    // Si le token commence par "-", on ajoute la valeur -1 plusieurs fois à la
    // liste
    if (value <= 0) {

      int repetitions = abs(value);
      // printf("Repetitions : %d\n", repetitions);
      for (int i = 0; i < repetitions; i++) {
        // Ajout de la valeur -1 à la liste
        resultList[count++] = -1;
      }
    } else if (value > autonomie) {
      // Ajout de -1 par pas atteignable
      resultList[count++] = -1;
    } else {
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

int index_of_distance(int a, int b) {

  if (a == b) {
    return (0);
  }
  if (a < b) {
    return (a + b * (b - 1) / 2);
  }
  if (a > b) {
    return (b + a * (a - 1) / 2);
  }
  return (-1);
}

void getBornesNumberFromIndex(int indexDistance, int *idBorne1, int *idBorne2) {
  int i = 1;
  int sum = 0;
  while (indexDistance >= sum) {
    sum += i;
    i++;
  }
  i--;
  *idBorne1 = i;
  *idBorne2 = indexDistance - (sum - i);
}
