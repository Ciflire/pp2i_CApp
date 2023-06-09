#include "../include/csvParser.h"
#include "../include/data_importer.h"
#include "../include/pathfinding.h"
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 1) {
    printf("Usage: %s\n", argv[0]);
    exit(1);
  }
  int seed = atoi(argv[0]);

  char *file_path = "data/borne-test.csv";
  csv_import *file = csv_import_create(1047, 4);
  csvParser(file_path, 0, file);
  borne_list *list_borne = borne_list_create();
  // import the data to a bornes_list
  borne_data_importer(file, list_borne);
  csv_import_destroy(file);

  char *file_path2 = "data/Vehicules.csv";
  csv_import *file2 = csv_import_create(MAX_LINES_CARS, 3);
  csvParser(file_path2, 0, file2);
  car_list *list_car = car_list_create();
  // import the data to a bornes_list
  car_data_importer(file2, list_car);
  csv_import_destroy(file2);

  char *file_path3 = "data/borne-test2.csv";
  csv_import *file3 = csv_import_create(3625, 4);
  csvParser(file_path3, 0, file3);
  borne_list *list_borne2 = borne_list_create();
  // import the data to a bornes_list
  borne_data_importer(file3, list_borne2);
  csv_import_destroy(file3);
  char *file_path4 = "data/borne_cleaned.csv";
  csv_import *file4 = csv_import_create(MAX_LINES_BORNES, 4);
  csvParser(file_path4, 1, file4);
  borne_list *list_borne3 = borne_list_create();
  // import the data to a bornes_list
  borne_data_importer(file4, list_borne3);
  csv_import_destroy(file4);

  borne *bretagne = borne_list_getBorne(list_borne);
  borne *nancy = borne_list_getBorne(list_borne->next);
  borne *paris = borne_list_getBorneById(list_borne, 632);
  borne *paris2 = borne_list_getBorneById(list_borne, 654);
  borne *pont_l_abbe = borne_list_getBorne(list_borne2);
  borne *bayonne = borne_list_getBorne(list_borne2->next);
  borne *painpol = borne_list_getBorneById(list_borne3, 474);
  borne *brest = borne_list_getBorneById(list_borne3, 64);
  borne *landivisiau = borne_list_getBorneById(list_borne3, 178);

  car *v1 = car_list_getCar(list_car);
  car *v2 = car_list_getCarById(list_car, 188);
  car *v3 = car_list_getCarById(list_car, 287);
  car *v4 = car_list_getCarById(list_car, 286);

  // test distance
  int dist_bretagne_nancy = distance(bretagne->latitude, bretagne->longitude,
                                     nancy->latitude, nancy->longitude);
  int dist_nancy_bretagne = distance(nancy->latitude, nancy->longitude,
                                     bretagne->latitude, bretagne->longitude);
  assert(dist_bretagne_nancy == dist_nancy_bretagne);
  assert(dist_bretagne_nancy <= 564);
  assert(dist_bretagne_nancy >= 560);

  int dist_nancy_nancy = distance(nancy->latitude, nancy->longitude,
                                  nancy->latitude, nancy->longitude);
  assert(dist_nancy_nancy == 0);

  int dist_paris_nancy = distance(paris->latitude, paris->longitude,
                                  nancy->latitude, nancy->longitude);
  assert(dist_paris_nancy <= 281);
  assert(dist_paris_nancy >= 277);

  printf("      [debug pathFiding_test] test_distance passed\n");

  // test travelTime

  borne *calais = borne_create(2000, 2, 22, 50.950, 1.859);
  int t1 = travelTime(bretagne, nancy, paris, v1, 666, 666);
  int t2 = travelTime(bretagne, nancy, calais, v1, 666, 666);
  assert(t2 > t1);

  printf("      [debug pathFiding_test] test_travelTime passed\n");

  // test timeToCharge
  int t3 = timeToCharge(paris, 666, v2, bretagne);
  int t4 = timeToCharge(paris2, 666, v2, bretagne);
  assert(t3 > t4);
  printf("charging_time is : %d\n", t3);
  printf("      [debug pathFiding_test] test_timeToCharge passed\n");

  // test creationZone
  borne_list *zone1 = borne_list_create();
  creationZone(bretagne, nancy, 0.6, v2, list_borne, zone1);
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
  creationZone(pont_l_abbe, bayonne, 0.9, v3, list_borne2, zone2);
  assert(borne_list_length(zone2) > 0);
  printf("zone2 is : \n");
  borne_list_print(zone2);
  printf("All points must be near this location : 47.81367071130333, "
         "-3.8348082559475722\n");
  printf("      [debug pathFiding_test] test_creationZone2 passed\n");

  // test findBestInZone
  borne_list *zone3 = borne_list_create();
  creationZone(painpol, brest, 0.8, v4, list_borne3, zone3);
  borne *best = malloc(sizeof(borne));
  double *bestTime = malloc(sizeof(double));
  findBestInZone(zone3, painpol, brest, v4, 6666, 6666, best, bestTime);
  assert(borne_equals(best, landivisiau));

  printf("      [debug pathFiding_test] test_findBestInZone passed\n");

  // test Pathfinding
  //[pathFinding] Test de chemin possible
  borne_list *path1 = borne_list_create();
  int error = pathFinding(v2, bretagne, nancy, path1, list_borne, 90, 120);
  assert(error == 0);
  borne_list_printPathLink(path1);
  free(path1);

  //[pathFinding] Test de chemin impossible
  borne_list *path2 = borne_list_create();
  error = pathFinding(v4, bretagne, nancy, path1, list_borne, 90, 120);
  assert(error == 1);
  free(path2);

  //[pathFinding] Test sur 10 chemins randoms
  for (int i = 0; i < 10; i++) {
    borne_list *path = borne_list_create();
    srand(seed);
    seed = rand();
    int car_id = rand() % (car_list_length(list_car) - 1);
    int id_origin = rand() % borne_list_length(list_borne3) + 1;
    int id_destination = rand() % borne_list_length(list_borne3) + 1;
    int battery_minimum = rand() % 30;
    int max_time_charging = (rand() % 120)+40;
    int max_time_waiting = (rand() % 60);

    error = pathFinding(car_list_getCarById(list_car, car_id),
                        borne_list_getBorneById(list_borne3, id_origin),
                        borne_list_getBorneById(list_borne3, id_destination),
                        path, list_borne3, battery_minimum, max_time_charging);
    if (error == 0) {
      borne_list_printPathLink(path);
    }
    free(path);
  }
  printf("      [debug pathFiding_test] test_pathFinding passed\n");


  
  borne_list_destroy(list_borne);
  borne_list_destroy(list_borne2);
  borne_list_destroy(list_borne3);
  car_list_destroy(list_car);
  free(bretagne);
  free(nancy);
  free(paris);
  free(paris2);
  free(pont_l_abbe);
  free(bayonne);
  free(painpol);
  free(brest);
  free(landivisiau);
  free(v1);
  free(v2);
  free(v3);
  free(v4);

}
