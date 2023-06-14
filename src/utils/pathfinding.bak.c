#include "../include/pathfinding.h"
#include "../include/borne_list.h"
#include "../include/car_list.h"
#include "../include/time_wait.h"
#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int distance(double lat1, double lon1, double lat2, double lon2) {
  // distance between latitudes
  // and longitudes
  double dLat = (lat2 - lat1) * M_PI / 180.0;
  double dLon = (lon2 - lon1) * M_PI / 180.0;

  // convert to radians
  lat1 = (lat1)*M_PI / 180.0;
  lat2 = (lat2)*M_PI / 180.0;

  // apply formulae
  double a =
      pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
  double rad = 6371;
  double c = 2 * asin(sqrt(a));
  return (int)rad * c;
}

/* // haversine distance
int distance(double latDep, double lonDep, double latArr, double lonArr) {
  float R = 6371.0; // km
  // printf("xDep, yDep, xArr, yArr : %lf, %lf, %lf, %lf\n", xDep, yDep, xArr,
  // yArr);
  // convert to radians
  float phi1 = lonDep * M_PI / 180.0; // φ, λ in radians
  float phi2 = lonArr * M_PI / 180.0;
  float lambda1 = latDep * M_PI / 180.0;
  float lambda2 = latArr * M_PI / 180.0;
  float deltaPhi = phi2 - phi1;
  float deltaLambda = lambda2 - lambda1;

  // printf("phi1, phi2, lambda1, lambda2 : %lf, %lf, %lf, %lf\n", phi1,
  // phi2,
  // lambda1, lambda2);
  // printf("deltaPhi, deltaLambda : %lf, %lf\n", deltaPhi, deltaLambda);

  // calculate distance
  float a =
      sin(deltaPhi / 2.0) * sin(deltaPhi / 2.0) +
      cos(phi1) * cos(phi2) * sin(deltaLambda / 2.0) * sin(deltaLambda / 2.0);

  printf("a : %lf\n", a);
  float d = 2.0 * R * asin(sqrt(a));
  // printf("d : %lf\n", d);
  return d;
} */

int creationZone(borne *actual, borne *ending, double p, car *usedCar,
                 borne_list *allListsBorne, borne_list *Zone,
                 borne_list *path) {
  if (p < 0) {
    printf("Error : p < 0\n");
    return 1;
  }
  // TODO: x and y are always equal to 0
  double lon = actual->longitude + (ending->longitude - actual->longitude) * p;
  double lat = actual->latitude + (ending->latitude - actual->latitude) * p;
  double lon_borne = actual->longitude;
  double lat_borne = actual->latitude;
  // printf("x,y: %lf, %lf\n", lon, lat);
  double autonomyAct = usedCar->autonomyAct;
  int n = borne_list_length(allListsBorne);
  borne_list *temp = allListsBorne;
  borne *borneInTest = temp->borne;
  for (int i = 0; i < n; i++) {
    /*     printf("distance(y, x, y_borne, x_borne) : %d\n",
               distance(y, x, y_borne, x_borne)); */
    // printf("%lf \n", (1 - p) * autonomyAct);
    // printf("%d \n", distance(x, y, x_borne, y_borne));

    if ((distance(lat_borne, lon_borne, borneInTest->latitude,
                  borneInTest->longitude) <= autonomyAct) &&
        (distance(lat, lon, borneInTest->latitude, borneInTest->longitude) <=
         (1 - p) * autonomyAct) &&
        !(borne_list_isBorneInList(path, borneInTest)) &&
        (borneInTest != actual)) {
      if (i < 5) {
        // printf("%d\n", distance(lat, lon, lat_borne, lon_borne));
        // borne_print(borneInTest);
      }
      borne_list_append(Zone, borneInTest);
    }
    temp = temp->next;
    borneInTest = temp->borne;
    lon_borne = borneInTest->longitude;
    lat_borne = borneInTest->latitude;
  }
  if (borne_list_length(Zone) == 0) {
    return creationZone(actual, ending, p - 0.1, usedCar, allListsBorne, Zone,
                        path);
  }
  return 0;
}

int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual) {
  int d = distance(borneC->latitude, borneC->longitude, borneActual->latitude,
                   borneActual->longitude);
  double timeToFullCharge =
      60.0 * car->capacity *
      (car->autonomyUsable - (car->autonomyAct - (float)d)) /
      (float)(borneC->power * car->autonomyMax);
  return MIN(timeToFullCharge, maxTimeCharging);
}

double travelTime(borne *actual, borne *goal) {
  double time = (60.0 / 130.0) * distance(actual->latitude, actual->longitude,
                                          goal->latitude, goal->longitude);
  // int chargeTime = timeToCharge(borneInTest, maxTimeCharging, car, actual);
  /*   printf("distanceActualBorne : %lf\n", distanceActualBorne);
    printf("distanceBorneEnd : %lf\n", distanceBorneEnd);
    printf("chargeTime : %d\n", chargeTime); */
  return time;
}

void isBorneBetterThanCurrentBestBorne(borne *best, double *bestTime,
                                       borne *borneInTest, borne *actual,
                                       borne *goal, int *bestPdcIndex,
                                       int *chargeTime, int *waitingTime,
                                       int *actualTime, int *travelTimeToGoal,
                                       int *travelTimeToBorneInTest,
                                       int *maxTimeCharging, car *car) {

  int chargeTimeTemp = timeToCharge(borneInTest, *maxTimeCharging, car, actual);
  int waitingTimeTemp = *waitingTime;
  int travelTimeToGoalTemp = *travelTimeToGoal;
  int travelTimeToBorneInTestTemp = *travelTimeToBorneInTest;
  int bestPdcIndexTemp = *bestPdcIndex;

  betterWaitTime(borneInTest, &waitingTimeTemp, &bestPdcIndexTemp, actualTime,
                 &chargeTimeTemp);

  travelTimeToBorneInTestTemp = travelTime(actual, borneInTest);
  travelTimeToGoalTemp = travelTime(borneInTest, goal);

  // printf("New totalTime : %d, Current totalTime : %d     Borne:%d  \n",
  //        waitingTimeTemp + chargeTimeTemp + travelTimeToBorneInTestTemp +
  //            travelTimeToGoalTemp,
  //        *waitingTime + *chargeTime + *travelTimeToBorneInTest +
  //            *travelTimeToGoal,
  //        borneInTest->id);

  // printf("%d %d %d %d\n", waitingTimeTemp, chargeTimeTemp,
  //        travelTimeToBorneInTestTemp, travelTimeToGoalTemp);
  // printf("%d %d %d %d\n", *waitingTime, *chargeTime,
  // *travelTimeToBorneInTest,
  //        *travelTimeToGoal);

  /* printf("%d , %d \n",
         waitingTimeTemp + chargeTimeTemp + travelTimeToBorneInTestTemp +
             travelTimeToGoalTemp,
         *waitingTime + *chargeTime + *travelTimeToBorneInTest +
             *travelTimeToGoal); */

  if (waitingTimeTemp + chargeTimeTemp + travelTimeToBorneInTestTemp +
          travelTimeToGoalTemp <=
      *waitingTime + *chargeTime + *travelTimeToBorneInTest +
          *travelTimeToGoal) {
    // printf("it's better\n");

    *bestTime = waitingTimeTemp + chargeTimeTemp + travelTimeToBorneInTestTemp +
                travelTimeToGoalTemp;
    *chargeTime = chargeTimeTemp;
    *waitingTime = waitingTimeTemp;
    *travelTimeToGoal = travelTimeToGoalTemp;
    *travelTimeToBorneInTest = travelTimeToBorneInTestTemp;
    *best = *borneInTest;
    *bestPdcIndex = bestPdcIndexTemp;
    // printf("Best ID: %d\n", best->id);
    // printf("Best ID: %d\n", best->id);
  }
}

void findBestInZone(borne_list *Zone, borne *actual, borne *goal, car *usedCar,
                    borne *best, double *bestTime, int *actualTime,
                    int *waitingTime, int *travelTimeToGoal,
                    int *travelTimeToBorneInTest, int *chargeTime,
                    int *maxTimeCharging) {
  /*   printf("%p\n", Zone->borne);
    borne_print(Zone->borne);
    borne_print(best); */

  *bestTime = travelTime(actual, best) + travelTime(best, goal);
  int bestPdc = 0;
  borne_list *borne_listInTest = Zone;

  for (int i = 1; i < borne_list_length(Zone); i++) {
    // get the first borne
    borne *borneInTest = borne_list_getBorne(borne_listInTest);
    // get the time to charge at the borne in test

    // if the borne in test better than the current best borne then
    // changes the best borne __ changes the best travel time __ changes
    // the best pdc
    isBorneBetterThanCurrentBestBorne(
        best, bestTime, borneInTest, actual, goal, &bestPdc, chargeTime,
        waitingTime, actualTime, travelTimeToGoal, travelTimeToBorneInTest,
        maxTimeCharging, usedCar);
    borne_listInTest = borne_list_getNext(borne_listInTest);
    // printf("%lf;%lf\n", borneInTest->latitude, borneInTest->longitude);

    /*     best = borneInTest;


        *(bestTime) = travelTime(actual, goal, best, usedCar,
       maxTimeCharging, maxTimeWaiting); */
    // printf("pdc : %d\n", bestPdc);
    // actualize the borne list in test
  }

  horaire *newCharge = horaire_createWithValues(
      *actualTime + *travelTimeToBorneInTest,
      *actualTime + *travelTimeToBorneInTest + *chargeTime);
  // printf("test : %d", best->pdc);

  // printf("test : %d", bestPdc);
  // printf("test : %p\n", (void *)best->horairePdc[bestPdc]);
  horaire_list_insert(best->horairePdc[bestPdc], newCharge);
}

int pathFinding(car *usedCar, borne *actual, borne *goal, borne_list *path,
                horaire_list *pathTime, borne_list *allListsBorne,
                int maxTimeWaiting, int maxTimeCharging, int *actualTime) {
  int waitingTime = maxTimeWaiting;
  int chargeTime = maxTimeCharging;
  int travelTimeToGoal = INT16_MAX;
  int travelTimeToBorneInTest = INT16_MAX;
  int pdcOptimal = 0;

  borne_list_append(path, actual);

  // borne_print(actual);

  // borne_print(goal);

  // printf("distance to goal: %d\n", distance(actual->longitude,
  // actual->latitude,
  //                                          goal->longitude, goal->latitude));
  printf("autonomy: %lf\n", usedCar->autonomyAct);

  if (distance(actual->latitude, actual->longitude, goal->latitude,
               goal->longitude) < usedCar->autonomyAct) {
    borne_list_append(path, goal);
    // TODO : add time to travel
    horaire_list_append(
        pathTime, horaire_createWithValues(
                      *actualTime, *actualTime /* + wait&charge&travel*/));
    return 0;
  } else {
    borne_list *Zone = borne_list_create();
    if (creationZone(actual, goal, 0.9, usedCar, allListsBorne, Zone, path)) {
      printf("error\n");
      return 1;
    }
    // borne_list_print(Zone);
    borne *best = borne_list_getBorne(Zone);
    /* for (int i = 0; i < borne_list_length(Zone); i++) {
      printf("pdc borne pointer : %p\n", (void *)best->horairePdc[i]);
    } */
    // borne_create(Zone->borne->id, Zone->borne->pdc,
    // Zone->borne->power,
    //              Zone->borne->latitude, Zone->borne->longitude);
    double *bestTime = malloc(sizeof(double));
    *bestTime =
        waitingTime + travelTimeToGoal + travelTimeToBorneInTest + chargeTime;
    /* printf("actual : %d\n", *actualTime); */
    findBestInZone(Zone, actual, goal, usedCar, best, bestTime, actualTime,
                   &waitingTime, &travelTimeToGoal, &travelTimeToBorneInTest,
                   &pdcOptimal, &chargeTime);
    // printf("best in zone is %d\n", best->id);

    free(Zone);

    horaire *newTravel = horaire_createWithValues(
        *actualTime + travelTimeToBorneInTest,
        *actualTime + travelTimeToBorneInTest + chargeTime + waitingTime);
    horaire_list_append(pathTime, newTravel);
    *actualTime += travelTimeToBorneInTest + chargeTime + waitingTime;
    // borne_list_print(path);
    // horaire_list_print(pathTime);
    // printf("goal : %d\n", goal->id);
    return pathFinding(usedCar, best, goal, path, pathTime, allListsBorne,
                       maxTimeWaiting, maxTimeCharging, actualTime);
  }
}
