#include "../include/pathfinding.h"
#include "../include/borne_list.h"
#include "../include/car_list.h"
#include <asm-generic/errno-base.h>

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
  double x = (ending->longitude - actual->longitude) * p *
             usedCar->autonomyAct / usedCar->autonomyUsable;
  double y = (ending->latitude - actual->latitude) * p * usedCar->autonomyAct /
             usedCar->autonomyUsable;
  double x_borne = actual->longitude;
  double y_borne = actual->latitude;
  double autonomyAct = usedCar->autonomyAct;
  int n = borne_list_length(allListsBorne);
  borne_list *temp = Zone;
  borne *borneInTest = Zone->borne;
  for (int i = 0; i < n; i++) {
    printf("x,y,x_borne,y_borne : %lf, %lf, %lf, %lf\n", x, y, x_borne,
           y_borne);
    if ((distance(x, y, x_borne, y_borne) <= ((1 - p) * autonomyAct)) &&
        !(borne_equals(actual, borneInTest))) {
      printf("yay we add a new borne to the zone\n");
      borne_list_append(Zone, borneInTest);
    }
    temp = temp->next;

    if (temp != NULL) {
      borneInTest = temp->borne;
      x_borne = borneInTest->longitude;
      y_borne = borneInTest->latitude;
    }
  }
  if (borne_list_length(Zone) == 0) {
    printf("we have to reduce the zone\n");
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
    borne *best = NULL;
    double *bestTime = NULL;
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
  maxTimeWaiting = 0; // TODO
  maxTimeWaiting++;
  return (60.0 / 130.0) *
             (distance(actual->latitude, actual->longitude,
                       borneInTest->longitude, borneInTest->latitude) +
              distance(borneInTest->longitude, borneInTest->latitude,
                       goal->longitude, goal->latitude)) +
         timeToCharge(borneInTest, maxTimeCharging, car,
                      actual); // add waiting time stuff
}

int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual) {
  int d = distance(borneC->latitude, borneC->longitude, borneActual->latitude,
                   borneActual->longitude);
  double timeToFullCharge = 60.0 * car->capacity * (car->autonomyAct - d) /
                            (borneC->power * car->autonomyMax);
  return MIN(timeToFullCharge, maxTimeCharging);
}
