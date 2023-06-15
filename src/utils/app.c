#include "../include/app.h"
#include "../include/csvParser.h"
#include "../include/data_importer.h"
#include "../include/pathfinding.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // check if arguments are numberOfCarSimulated and seed
  if (argc == 3) {
    int nbSimu = atoi(argv[1]);
    // check if the number of simulated car is valid
    if (nbSimu < 1) {
      printf("error: 0 travels\n");
      exit(1);
    }
    int seed = atoi(argv[2]);
    // importing the data from bornes_cleaned.csv
    char *file_path4 = "data/borne_cleaned.csv";
    line_array *file4 = line_array_create(MAX_LINES_BORNES, 4);
    csvParser(file_path4, 1, file4);
    borne_list *list_borne = borne_list_create();
    // import the data to a bornes_list
    borne_list_dataImporter(file4, list_borne);
    line_array_destroy(file4);

    // importing the cars from Vehicules.csv
    char *file_path2 = "data/Vehicules.csv";
    line_array *file2 = line_array_create(MAX_LINES_CARS, 3);
    csvParser(file_path2, 0, file2);
    car_list *list_car = car_list_create();
    // import the data to a bornes_list
    car_list_dataImporter(file2, list_car);
    line_array_destroy(file2);

    for (int i = 0; i < nbSimu; i++) {

      borne_list *path = borne_list_create();
      horaire_list *pathTime = horaire_list_create();
      srand(seed);
      seed = rand();
      int actualTime = rand() % 1800;
      int car_id = rand() % (287) + 1;
      int id_origin = rand() % borne_list_length(list_borne) + 1;
      int id_destination = rand() % borne_list_length(list_borne) + 1;
      int battery_minimum = rand() % 10;
      int max_time_charging = (rand() % 120) + 300;
      int max_time_waiting = (rand() % 300) + 300;
      car *car = car_list_getCarById(list_car, car_id);
      car->autonomyAct = car->autonomyMax * (1 - battery_minimum / 100.0);
      car->autonomyUsable = car->autonomyAct;
      horaire_list_append(pathTime,
                          horaire_createWithValues(actualTime, actualTime));
      int error = pathFinding(
          car, borne_list_getBorneById(list_borne, id_origin),
          borne_list_getBorneById(list_borne, id_destination), path, pathTime,
          list_borne, max_time_waiting, max_time_charging, &actualTime);
      if (error == 0) {
        borne_list_printPathLink(path);
                 /*        borne_list_savePathInPythonListFormat(path,
                    "response_borne.txt");
                       horaire_list_saveHorairePathInPythonListFormat(pathTime,
                                                                      "response_horaires.txt");
                  */
      }
      free(path);
      horaire_list_destroy(pathTime);
    }
    borne_list_destroy(list_borne);
    car_list_destroy(list_car);
  } else if (argc == 8) {
    int car_id = atoi(argv[1]);
    int id_origin = atoi(argv[2]);
    int actualTime = atoi(argv[3]);
    borne_list *path = borne_list_create();
    int id_destination = atoi(argv[4]);
    int battery_minimum = atoi(argv[5]);
    int max_time_charging = atoi(argv[6]);
    int max_time_waiting = atoi(argv[7]);
    horaire_list *pathTime = horaire_list_create();

    char *file_path4 = "data/borne_cleaned.csv";
    line_array *file4 = line_array_create(MAX_LINES_BORNES, 4);
    csvParser(file_path4, 1, file4);
    borne_list *list_borne = borne_list_create();
    // import the data to a bornes_list
    borne_list_dataImporter(file4, list_borne);
    line_array_destroy(file4);

    char *file_path2 = "data/Vehicules.csv";
    line_array *file2 = line_array_create(MAX_LINES_CARS, 3);
    csvParser(file_path2, 0, file2);
    car_list *list_car = car_list_create();
    // import the data to a bornes_list
    car_list_dataImporter(file2, list_car);
    line_array_destroy(file2);

    car *car = car_list_getCarById(list_car, car_id);
    car->autonomyAct = car->autonomyMax * (1 - battery_minimum / 100.0);
    car->autonomyUsable = car->autonomyAct;

    horaire_list_append(pathTime,
                        horaire_createWithValues(actualTime, actualTime));
    borne *actual = borne_list_getBorneById(list_borne, id_origin);
    borne *dest = borne_list_getBorneById(list_borne, id_destination);
    int error = pathFinding(car, actual, dest, path, pathTime, list_borne,
                            max_time_waiting, max_time_charging, &actualTime);
    if (error == 0) {
      borne_list_printPathLink(path);
      /* borne_list_printPathMapsIntegrator(path);
               borne_list_savePathInPythonListFormat(path,
         "response_borne.txt"); horaire_list_saveHorairePathInPythonListFormat(
                   pathTime, "response_horaires.txt");
               */
    }
    free(path);
    borne_list_destroy(list_borne);
    car_list_destroy(list_car);
    horaire_list_destroy(pathTime);
  } else {
    printf("error: wrong number of arguments\n");
    exit(1);
  }
}
