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

// haversine distance
int distance(double xDep, double yDep, double xArr, double yArr) {
  float R = 6371.0; // km
  // printf("xDep, yDep, xArr, yArr : %lf, %lf, %lf, %lf\n", xDep, yDep, xArr,
  // yArr);
  // convert to radians
  float phi1 = xDep * M_PI / 180.0; // φ, λ in radians
  float phi2 = xArr * M_PI / 180.0;
  float lambda1 = yDep * M_PI / 180.0;
  float lambda2 = yArr * M_PI / 180.0;
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

  // printf("a : %lf\n", a);
  float d = 2.0 * R * asin(sqrt(a));
  // printf("d : %lf\n", d);
  return d;
}

int creationZone(borne *actual, borne *ending, double p, car *usedCar,
                 borne_list *allListsBorne, borne_list *Zone) {
  if (p < 0) {
    printf("Error : p < 0\n");
    return 1;
  }
  // TODO: x and y are always equal to 0
  double x = actual->longitude + (ending->longitude - actual->longitude) * p *
                                     usedCar->autonomyAct /
                                     usedCar->autonomyUsable;
  double y = actual->latitude + (ending->latitude - actual->latitude) * p *
                                    usedCar->autonomyAct /
                                    usedCar->autonomyUsable;

  double x_borne = actual->longitude;
  double y_borne = actual->latitude;
  double autonomyAct = usedCar->autonomyAct;
  int n = borne_list_length(allListsBorne);
  borne_list *temp = allListsBorne;
  borne *borneInTest = temp->borne;
  for (int i = 0; i < n; i++) {
    if ((distance(x, y, x_borne, y_borne) <= ((1 - p) * autonomyAct)) &&
        !(borne_equals(actual, borneInTest))) {
      borne_list_append(Zone, borneInTest);
    }
    temp = temp->next;
    borneInTest = temp->borne;
    x_borne = borneInTest->longitude;
    y_borne = borneInTest->latitude;
  }
  if (borne_list_length(Zone) == 0) {
    return creationZone(actual, ending, p - 0.1, usedCar, allListsBorne, Zone);
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
  double time = (60.0 / 130.0) * distance(actual->longitude, actual->latitude,
                                          goal->longitude, goal->latitude);
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

  betterWaitTime(borneInTest, &waitingTimeTemp, bestPdcIndex, actualTime,
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

  if (waitingTimeTemp + chargeTimeTemp + travelTimeToBorneInTestTemp +
          travelTimeToGoalTemp <
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
  // printf("%p\n", best->horaires_pdc[bestPdc]);
  horaire_list_insert(best->horaires_pdc[bestPdc], newCharge);
}

int pathFinding(car *usedCar, borne *actual, borne *goal, borne_list *path,
                horaire_list *pathTime, borne_list *allListsBorne,
                int maxTimeWaiting, int maxTimeCharging, int *actualTime) {
  int waitingTime = maxTimeWaiting;
  int chargeTime = maxTimeCharging;
  int travelTimeToGoal = INT16_MAX;
  int travelTimeToBorneInTest = INT16_MAX;
  int pdcOptimal = 0;

  if (distance(actual->longitude, actual->latitude, goal->longitude,
               goal->latitude) < usedCar->autonomyAct) {
    borne_list_append(path, goal);
    // TODO : add time to travel
    horaire_list_append(
        pathTime, horaire_createWithValues(
                      *actualTime, *actualTime /* + wait&charge&travel*/));
    return 0;
  } else {
    borne_list *Zone = borne_list_create();
    creationZone(actual, goal, 0.9, usedCar, allListsBorne, Zone);
    borne *best = borne_list_getBorne(Zone);
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
    printf("best in zone is %d\n", best->id);

    free(Zone);

    borne_list_append(path, best);
    horaire *newTravel = horaire_createWithValues(
        *actualTime + travelTimeToBorneInTest,
        *actualTime + travelTimeToBorneInTest + chargeTime + waitingTime);
    horaire_list_append(pathTime, newTravel);
    *actualTime += travelTimeToBorneInTest + chargeTime + waitingTime;

    return pathFinding(usedCar, best, goal, path, pathTime, allListsBorne,
                       maxTimeWaiting, maxTimeCharging, actualTime);
  }
}
