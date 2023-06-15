#include "../include/csvParser.h"
#include "../include/data_importer.h"
#include "../include/pathfinding.h"
#include "../include/timer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* if (argc != 2) {
    printf("Usage: %s\n", argv[0]);
    exit(1);
  } */
  // int seed = atoi(argv[1]);
  int seed = 12;
  char *file_path = "data/borne-test.csv";
  line_array *file = line_array_create(1047, 4);
  csvParser(file_path, 0, file);
  borne_list *list_borne = borne_list_create();

  // import the data to a bornes_list
  borne_list_dataImporter(file, list_borne);
  line_array_destroy(file);

  char *file_path2 = "data/Vehicules.csv";
  line_array *file2 = line_array_create(MAX_LINES_CARS, 3);
  csvParser(file_path2, 0, file2);
  car_list *list_car = car_list_create();

  // import the data to a bornes_list
  car_list_dataImporter(file2, list_car);
  line_array_destroy(file2);

  char *file_path3 = "data/borne-test2.csv";
  line_array *file3 = line_array_create(3625, 4);
  csvParser(file_path3, 0, file3);
  borne_list *list_borne2 = borne_list_create();

  // import the data to a bornes_list
  borne_list_dataImporter(file3, list_borne2);
  line_array_destroy(file3);

  char *file_path4 = "data/borne_cleaned.csv";
  line_array *file4 = line_array_create(MAX_LINES_BORNES, 4);
  csvParser(file_path4, 1, file4);
  borne_list *list_borne3 = borne_list_create();
  // import the data to a bornes_list
  borne_list_dataImporter(file4, list_borne3);
  line_array_destroy(file4);

  borne *bretagne = borne_list_getBorne(list_borne);
  borne *nancy = borne_list_getBorne(list_borne->next);
  borne *paris = borne_list_getBorneById(list_borne, 632);
  borne *paris2 = borne_list_getBorneById(list_borne, 654);
  borne *pont_l_abbe = borne_list_getBorne(list_borne2);
  borne *bayonne = borne_list_getBorne(list_borne2->next);
  borne *painpol = borne_list_getBorneById(list_borne3, 474);
  borne *brest = borne_list_getBorneById(list_borne3, 64);
  borne *landivisiau = borne_list_getBorneById(list_borne3, 177);
  borne *calais = borne_create(2000, 2, 7, 50.950, 1.859);

  car *v1 = car_list_getCar(list_car);
  car *v2 = car_list_getCarById(list_car, 188);
  car *v3 = car_list_getCarById(list_car, 287);
  car *v4 = car_list_getCarById(list_car, 286);

  // test distance
  int dist_nancy_nancy = distance(nancy->latitude, nancy->longitude,
                                  nancy->latitude, nancy->longitude);
  assert(dist_nancy_nancy == 0);

  int dist_paris_nancy = distance(paris->latitude, paris->longitude,
                                  nancy->latitude, nancy->longitude);
  assert(dist_paris_nancy <= 281);
  assert(dist_paris_nancy >= 277);
  int dist_bretagne_nancy = distance(bretagne->latitude, bretagne->longitude,
                                     nancy->latitude, nancy->longitude);
  int dist_nancy_bretagne = distance(nancy->latitude, nancy->longitude,
                                     bretagne->latitude, bretagne->longitude);
  assert(dist_bretagne_nancy == dist_nancy_bretagne);
  assert(dist_bretagne_nancy <= 564);
  assert(dist_bretagne_nancy >= 560);

  printf("      [debug pathFiding_test] test_distance passed\n");

  // test travelTime

  int t1 = travelTime(bretagne, paris) + travelTime(nancy, paris);
  int t2 = travelTime(bretagne, calais) + travelTime(calais, nancy);
  assert(t1 < t2);

  printf("      [debug pathFiding_test] test_travelTime passed\n");

  // test timeToCharge
  int t3 = timeToCharge(paris, 666, v2, bretagne);
  int t4 = timeToCharge(paris2, 666, v2, bretagne);
  assert(t3 > t4);
  printf("      [debug pathFiding_test] test_timeToCharge passed\n");

  // test creationZone
  borne_list *zone1 = borne_list_create();
  creationZone(bretagne, nancy, 0.9, v2, list_borne, zone1,
               borne_list_create());
  assert(borne_list_length(zone1) == 1045);
  v1->autonomyAct = 402;
  for (int i = 0; i < borne_list_length(zone1); i++) {
    assert(distance(bretagne->latitude, bretagne->longitude,
                    zone1->borne->latitude,
                    zone1->borne->longitude) <= v1->autonomyAct);
    zone1 = zone1->next;
  }
  printf("      [debug pathFiding_test] test_creationZone1 passed\n");

  borne_list *zone2 = borne_list_create();
  creationZone(pont_l_abbe, bayonne, 0.9, v3, list_borne2, zone2,
               borne_list_create());
  assert(borne_list_length(zone2) > 0);

  // test findBestInZone
  borne_list *zone3 = borne_list_create();
  creationZone(painpol, brest, 0.6, v4, list_borne3, zone3,
               borne_list_create());
  double *bestTime = malloc(sizeof(double));
  int actualTime = 1;
  int waitingTime = 99999;
  int travelTimeToGoal = 99999;
  int travelTimeToBorneInTest = 999999;
  int maxTimeCharging = 999999;
  int bestChargeTime = 99999;
  int bestPdcIndex = 0;

  borne *best = findBestInZone(zone3, painpol, brest, v4, bestTime, &actualTime,
                               &waitingTime, &travelTimeToGoal,
                               &travelTimeToBorneInTest, &bestChargeTime,
                               &maxTimeCharging, &waitingTime, &bestPdcIndex);
  assert(borne_equals(best, landivisiau));

  printf("      [debug pathFiding_test] test_findBestInZone passed\n");

  // // test Pathfinding
  //[pathFinding] Test de chemin possible
  int actualTime2 = 1;
  borne_list *path1 = borne_list_create();
  horaire_list *pathTime1 = horaire_list_create();
  int error = pathFinding(v1, bretagne, nancy, path1, pathTime1, list_borne, 90,
                          120, &actualTime2);
  assert(error == 0);
  free(path1);
  horaire_list_destroy(pathTime1);
  printf("      [debug pathFiding_test] test_pathFinding1 passed\n");

  //[pathFinding] Test de chemin impossible
  borne_list *path2 = borne_list_create();
  horaire_list *pathTime2 = horaire_list_create();
  error = pathFinding(v4, bretagne, nancy, path2, pathTime2, list_borne, 90,
                      120, &actualTime);
  assert(error == 1);
  free(path2);
  horaire_list_destroy(pathTime2);
  printf("      [debug pathFiding_test] test_pathFinding2 passed\n");

  for (int j = 0; j < 4; j++) {
    //[pathFinding] Test sur 10^j chemins randoms
    timer_start();
    for (int i = 0; i < pow(10, j); i++) {

      int actualTime = 0;
      borne_list *path = borne_list_create();
      horaire_list *pathTime = horaire_list_create();
      srand(seed);
      seed = rand();
      int car_id = rand() % (287) + 1;
      int id_origin = rand() % (14759) + 1;
      int id_destination = rand() % (14759) + 1;
      int battery_minimum = rand() % 10;
      int max_time_charging = (rand() % 120) + 300;
      int max_time_waiting = (rand() % 300) + 300;
      if (id_origin == 89) {
        id_origin++;
      }
      if (id_destination == 89) {
        id_destination++;
      }
      car *car = car_list_getCarById(list_car, car_id);
      car->autonomyAct = car->autonomyMax * (1 - battery_minimum / 100.0);
      car->autonomyUsable = car->autonomyAct;
      error = pathFinding(car, borne_list_getBorneById(list_borne3, id_origin),
                          borne_list_getBorneById(list_borne3, id_destination),
                          path, pathTime, list_borne3, max_time_waiting,
                          max_time_charging, &actualTime);
      free(path);
      horaire_list_destroy(pathTime);
    }
    timer_stop();
    timer_print();
  }
  printf("      [debug pathFiding_test] test_pathFinding3 passed\n");
  borne_list_destroy(list_borne);
  borne_list_destroy(list_borne2);
  borne_list_destroy(list_borne3);
  car_list_destroy(list_car);
  borne_destroy(calais);
}
