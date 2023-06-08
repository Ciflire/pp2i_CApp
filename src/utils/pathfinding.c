#include "../include/pathfinding.h"
#include "../include/borne_list.h"
#include "../include/car_list.h"
#include <asm-generic/errno-base.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// haversine distance
int distance(double xDep, double yDep, double xArr, double yArr) {
  double R = 6371;
  double varLong = (xArr - xDep) * M_PI / 180.0;
  double varLat = (yArr - yDep) * M_PI / 180.0;
  double a = sin(varLat / 2.0) * sin(varLat / 2.0) +
             cos(yDep * M_PI / 180) * cos(yArr * M_PI / 180.0) *
                 sin(varLong / 2.0) * sin(varLong / 2.0);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int d = (int)R * c;
  return d;
}

int creationZone(borne *actual, borne *ending, double p, car *usedCar,
                 borne_list *allListsBorne, borne_list *Zone) {
  if (p < 0) {
    return 1;
  }
  double x = (ending->longitude - actual->longitude) * p *
             usedCar->autonomyAct / usedCar->autonomyUsable;
  double y = (ending->latitude - actual->latitude) * p * usedCar->autonomyAct /
             usedCar->autonomyUsable;
  double x_borne = actual->longitude;
  double y_borne = actual->latitude;
  double autonomyAct = usedCar->autonomyAct;
  int n = borne_list_length(allListsBorne);
  borne *borneInTest = Zone->borne;
  for (int i = 0; i < n; i++) {
    if ((distance(x, y, x_borne, y_borne) <= ((1 - p) * autonomyAct)) &&
        !(borne_equals(actual, borneInTest))) {
      borne_list_append(Zone, borneInTest);
    }
  }
  if (borne_list_length(Zone) == 0) {
    return creationZone(actual, ending, p - 0.1, usedCar, allListsBorne, Zone);
  }
  return 0;
}

int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path,
                borne_list *allListsBorne, int maxTimeWaiting,
                int maxTimeCharging) {
  if (distance(actual->longitude, actual->latitude, ending->longitude,
               ending->latitude) < usedCar->autonomyAct) {
    borne_list_append(path, ending);
    return 0;
  } else {
    borne_list *Zone = borne_list_create();
    creationZone(actual, ending, 0.9, usedCar, allListsBorne, Zone);
    borne *best;
    double *bestTime;
    findBestInZone(Zone, actual, ending, usedCar, maxTimeCharging,
                   maxTimeWaiting, best, bestTime);
    borne_list_append(path, best);
    return pathFinding(usedCar, best, ending, path, allListsBorne,
                       maxTimeWaiting, maxTimeCharging);
  }

  return 0;
}

void findBestInZone(borne_list *Zone, borne *actual, borne *goal, car *usedCar,
                    int maxTimeCharging, int maxTimeWaiting, borne *best,
                    double *bestTime) {
  best = borne_list_getBorne(Zone);
  *(bestTime) =
      travelTime(actual, goal, best, usedCar, maxTimeCharging, maxTimeWaiting);
  borne_list *borne_listInTest = Zone;
  for (int i = 1; i < borne_list_length(Zone); i++) {
    borne_listInTest = borne_list_getNext(borne_listInTest);
    if (isBorneBetterThanCurrentBestBorne(
            bestTime, borne_list_getBorne(borne_listInTest), actual, goal,
            usedCar, maxTimeWaiting, maxTimeCharging)) {
      best = borne_list_getBorne(borne_listInTest);
      *(bestTime) = travelTime(actual, goal, best, usedCar, maxTimeCharging,
                               maxTimeWaiting);
    }
  }
}

bool isBorneBetterThanCurrentBestBorne(double *bestTime, borne *borneInTest,
                                       borne *actual, borne *goal, car *car,
                                       int maxTimeWaiting,
                                       int maxTimeCharging) {
  return travelTime(actual, goal, borneInTest, car, maxTimeCharging,
                    maxTimeWaiting) < *(bestTime);
}

double travelTime(borne *actual, borne *goal, borne *borneInTest, car *car,
                  int maxTimeCharging, int maxTimeWaiting) {
  return (60.0 / 130.0) *
             (distance(actual->latitude, actual->longitude,
                       borneInTest->longitude, borneInTest->latitude) +
              distance(borneInTest->longitude, borneInTest->latitude,
                       goal->longitude, goal->latitude)) +
         timeToCharge(borneInTest, maxTimeCharging,
                      car); // add waiting time stuff
}

int timeToCharge(borne *borne, int maxTimeCharging, car *car) {
  double timeToFullCharge = 60.0 * car->capacity *
                            (car->autonomyUsable - car->autonomyAct) /
                            (borne->power * car->autonomyMax);
  return MIN(timeToFullCharge, maxTimeCharging);
}
