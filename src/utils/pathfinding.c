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

// harversine distance in km
int distance(double lat1, double lon1, double lat2, double lon2) {
  double dLat = (lat2 - lat1) * M_PI / 180.0;
  double dLon = (lon2 - lon1) * M_PI / 180.0;

  lat1 = (lat1)*M_PI / 180.0;
  lat2 = (lat2)*M_PI / 180.0;

  double a =
      pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
  double rad = 6371;
  double c = 2 * asin(sqrt(a));
  return (int)(rad * c);
}

// creates a zone around certain coordinates that the car can reach and that is
// not already in the path and different that the borne we are on if the zone is
// empty at the end, we call the function with a lower p until it gets negative
// and returns an error

int creationZone(borne *actual, borne *ending, double p, car *usedCar,
                 borne_list *allListsBorne, borne_list *Zone,
                 borne_list *path) {
  if (p < 0) {
    return 1;
  }
  double centerLon =
      actual->longitude + (ending->longitude - actual->longitude) * p;
  double centerLat =
      actual->latitude + (ending->latitude - actual->latitude) * p;

  double depLon = actual->longitude;
  double depLat = actual->latitude;

  int n = borne_list_length(allListsBorne);

  borne_list *spot = allListsBorne;
  for (int i = 0; i < n; i++) {
    if (distance(centerLat, centerLon, spot->borne->latitude,
                 spot->borne->longitude) <= (1 - p) * usedCar->autonomyAct &&
        distance(depLat, depLon, spot->borne->latitude,
                 spot->borne->longitude) <= usedCar->autonomyAct &&
        !borne_list_isBorneInList(path, spot->borne) &&
        !borne_list_isBorneInList(Zone, spot->borne) &&
        !borne_list_isBorneInList(Zone, actual)) {
      borne_list_append(Zone, spot->borne);
    }
    spot = spot->next;
  }
  if (borne_list_length(Zone) == 0) {
    return creationZone(actual, ending, p - 0.1, usedCar, allListsBorne, Zone,
                        path);
  }
  return 0;
}

// returns the time to charge the car at a certain borne according to the
// distance between the actual borne and the goal borne
int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual) {
  int time = 0;
  int travelDistance = distance(borneActual->latitude, borneActual->longitude,
                                borneC->latitude, borneC->longitude);
  time = MIN(maxTimeCharging, 60.0 * car->capacity *
                                  (car->autonomyUsable -
                                   (car->autonomyAct - (float)travelDistance)) /
                                  (float)(borneC->power * car->autonomyMax));
  return time;
}

// returns the travel time between two bornes in minutes
double travelTime(borne *actual, borne *goal) {
  double time = (60.0 / 130.0) * distance(actual->latitude, actual->longitude,
                                          goal->latitude, goal->longitude);
  return time;
}

// If the borneInTest is better than the bestBorne, we change the bestBorne and
// actualize the bestTime, charge time, waiting time, travelTimeToGoal,
// travelTimeToBorneInTest, and bestPdcIndex

void updateBestBorne(borne *actual, borne *goal, borne *borneInTest,
                     borne *bestBorne, double *bestTime, int *chargeTime,
                     int *waitingTime, int *travelTimeToGoal,
                     int *travelTimeToBorneInTest, int *bestPdcIndex,
                     car *usedCar, int maxTimeCharging, int maxTimeWaiting,
                     int currentTime) {
  double timeToGoal = travelTime(borneInTest, goal);
  double timeToBorneInTest = travelTime(actual, borneInTest);
  int timeToChargeCar =
      timeToCharge(borneInTest, maxTimeCharging, usedCar, actual);
  int bestPdcIndexInTest = 0;
  int waitingTimeInTest = 0;

  betterWaitTime(borneInTest, &waitingTimeInTest, &bestPdcIndexInTest,
                 &currentTime, &timeToChargeCar);

  if (timeToGoal + timeToBorneInTest + timeToChargeCar + waitingTimeInTest <=
          *travelTimeToGoal + *travelTimeToBorneInTest + *chargeTime +
              *waitingTime &&
      waitingTimeInTest <= maxTimeWaiting) {
    *bestBorne = *borneInTest;
    *bestTime =
        timeToGoal + timeToBorneInTest + timeToChargeCar + waitingTimeInTest;
    *chargeTime = timeToChargeCar;
    *waitingTime = waitingTimeInTest;
    *travelTimeToGoal = timeToGoal;
    *travelTimeToBorneInTest = timeToBorneInTest;
    *bestPdcIndex = bestPdcIndexInTest;
  }
}

// returns the best borne to go to according to the goal borne and the actual in
// a zone
void findBestInZone(borne_list *Zone, borne *actual, borne *goal, car *usedCar,
                    borne *best, double *bestTime, int *actualTime,
                    int *waitingTime, int *travelTimeToGoal,
                    int *travelTimeToBorneInTest, int *chargeTime,
                    int *maxTimeCharging, int *maxTimeWaiting,
                    int *bestPdcIndex) {
  int n = borne_list_length(Zone);
  borne_list *spot = Zone;

  // we test every borne of the zone if is better than the best borne
  for (int i = 0; i < n; i++) {
    borne *borneInTest = borne_list_getBorne(spot);
    updateBestBorne(actual, goal, borneInTest, best, bestTime, chargeTime,
                    waitingTime, travelTimeToGoal, travelTimeToBorneInTest,
                    bestPdcIndex, usedCar, *maxTimeCharging, *maxTimeWaiting,
                    *actualTime);
    spot = spot->next;
  }
}

// find the best path to go to the goal borne from the actual borne
// add to pathTime (actualTime, actualTime) in app
int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path,
                horaire_list *pathTime, borne_list *allListsBorne,
                int maxTimeWaiting, int maxTimeCharging, int *actualTime) {
  borne_list_append(path, actual);
  if (distance(actual->latitude, actual->longitude, ending->latitude,
               ending->longitude) <= usedCar->autonomyAct) {
    borne_list_append(path, ending);
    horaire_list_append(
        pathTime, horaire_createWithValues(
                      *actualTime, *actualTime + travelTime(actual, ending)));
    return 0;
  } else {
    borne_list *Zone = borne_list_create();
    creationZone(actual, ending, 1, usedCar, allListsBorne, Zone, path);
    if (borne_list_length(Zone) == 0) {
      return 1;
    }
    borne *best = borne_list_getBorne(Zone);
    // Each time, if the goal is unreachable it means we initialize the travel
    // time to the goal to unspeakable values and also the waiting time to be
    // sure we will find better
    // Please not tha the first borne is also tested in the function
    double bestTime = (float)INT32_MAX;
    int waitingTime = INT32_MAX;
    int travelTimeToGoal = INT32_MAX;
    int travelTimeToBorneInTest = INT32_MAX;
    int chargeTime = INT32_MAX;
    int bestPdcIndex = 0;
    // printf("autonomyAct : %f\n", usedCar->autonomyAct);
    findBestInZone(Zone, actual, ending, usedCar, best, &bestTime, actualTime,
                   &waitingTime, &travelTimeToGoal, &travelTimeToBorneInTest,
                   &chargeTime, &maxTimeCharging, &maxTimeWaiting,
                   &bestPdcIndex);
    free(Zone);
    horaire_list_append(
        pathTime,
        horaire_createWithValues(*actualTime + travelTimeToBorneInTest,
                                 *actualTime + bestTime - travelTimeToGoal));
    horaire_list_insert(best->horairePdc[bestPdcIndex],
                        horaire_createWithValues(
                            *actualTime + travelTimeToGoal + waitingTime,
                            *actualTime + bestTime - travelTimeToBorneInTest));
    actualTime += (int)bestTime - travelTimeToGoal;
    return pathFinding(usedCar, best, ending, path, pathTime, allListsBorne,
                       maxTimeWaiting, maxTimeCharging, actualTime);
  }
}
