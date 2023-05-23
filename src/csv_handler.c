#include "include/csv_handler.h"

// generates the graph based on the csv
bornes_graph *generate_graph_fromCSV(int autonomie,
                                     bornes_list *list_de_toutes_les_bornes,
                                     int *distances) {
  // creates a file pointer
  FILE *f_adjacence;
  printf("in generate_graph_fromCSV\n");
  // opens the file
  f_adjacence = fopen("data/adjacence.csv", "r");

  // check if the file exists or is open
  if (!f_adjacence) {
    printf("Can't open file adjacence.csv\n");
    return (NULL);
  }

  // creates a string to store the csv line
  char *csvLine = (char *)malloc(184099266);

  // reads the first line of the csv which is the entire file
  fgets(csvLine, 184099266, f_adjacence);

  // closes the file
  fclose(f_adjacence);
  int resultSize;

  generateListFromCSV(csvLine, distances, &resultSize, autonomie);
  printf("resultSize = %d\n", resultSize);
  FILE *fp;
  char row[50];

  fp = fopen("data/bornes.csv", "r");

  // check if the file exists or is open
  if (!fp) {
    printf("Can't open file bornes.csv\n");
    return (NULL);
  }

  bornes_graph *bg = create_bornes_graph(NB_BORNES);
  printf("bg created\n");
  // création de la liste de toutes les bornes

  int id = 0;
  
  char* token;
  while (!feof(fp)) {
    fgets(row, 40000, fp);
    if (id == NB_BORNES) {
      continue;
    }
    double xpos;
    double ypos;
    double power;
    int qte;
    // NULL permet d'avancer d'un token
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
    if (distances[i] != -1) {
      int borne1;
      int borne2;
      getBornesNumberFromIndex(i, &borne1, &borne2);

      add_borne_index(bg, borne1, get_borne(list_de_toutes_les_bornes, borne2));
      add_borne_index(bg, borne2, get_borne(list_de_toutes_les_bornes, borne1));
    }
  }
  free(distances);
  free(csvLine);
  destroy_bornes_list(list_de_toutes_les_bornes);

  return bg;
}

void generateListFromCSV(char *csvLine, int *resultList, int *resultSize,
                         int autonomie) {
  // Initialisation des variables
  int count = 0;
  int count_links = 0;
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
      count_links++;
    }

    // Passage au token suivant
    token = strtok(NULL, ",");
  }
  free(token);

  // Affectation des résultats
  *resultSize = count;
  printf("count_links = %d\n", count_links);
}


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

void getCarInfos(vehicule_list *v_list) {
  FILE *f_car;
  char row[100];
  // Gets the file from were we execute the program
  f_car = fopen("data/Vehicules.csv", "r");

  // check if the file exists or is open
  if (!f_car) {
    printf("Can't open file Véhicules.csv\n");
    return;
  }
  char *csvLine = (char *)malloc(6000);
  fgets(csvLine, 6000, f_car);
  int id = 0;
  int autonomie;
  double capacity;
  while (!feof(f_car)) {
    fgets(row, 100000, f_car);
    char *name = (char *)strtok(row, ",");
    autonomie = atoi(strtok(NULL, ","));
    capacity = atoi(strtok(NULL, ","));
    add_vehicule(v_list, create_vehicule(id, name, autonomie, capacity));
    id++;
  }
  fclose(f_car);
  free(csvLine);

  return;
}
