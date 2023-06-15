#include "../include/pathfinding.h"

// harversine distance in km
int distance(double lat1, double lon1, double lat2, double lon2) {
  // Defines the diference of longitude and latitude in radian
  double dLat = (lat2 - lat1) * M_PI / 180.0;
  double dLon = (lon2 - lon1) * M_PI / 180.0;

  lat1 = (lat1)*M_PI / 180.0;
  lat2 = (lat2)*M_PI / 180.0;

  // Haversine formula
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
  if (p < 0) { // if p is negative, no neighbour is reachable
    return 1;
  }

  // Define the center coordinates of the zone
  double centerLon =
      actual->longitude + (ending->longitude - actual->longitude) * p;
  double centerLat =
      actual->latitude + (ending->latitude - actual->latitude) * p;

  double depLon = actual->longitude;
  double depLat = actual->latitude;

  int n = borne_list_length(allListsBorne);

  borne_list *spot = allListsBorne;
  for (int i = 0; i < n; i++) { // for all bornes
    if (distance(centerLat, centerLon, spot->borne->latitude,
                 spot->borne->longitude) <=
            (1 - p) * usedCar->autonomyAct && // if the borne is in the zone
                                              // (radius of (1-p)* AutonomyAct)
        distance(depLat, depLon, spot->borne->latitude,
                 spot->borne->longitude) <=
            usedCar->autonomyAct && // and if the borne is reachable from the
                                    // actual borne
        !borne_list_isBorneInList(
            path, spot->borne) && // and if the borne is not already in the path
        !borne_list_isBorneInList(Zone,
                                  spot->borne) && // and if the borne is
                                                  // not already in the zone
        !borne_list_isBorneInList(
            Zone, actual)) { // and if the borne is not the actual borne
      borne_list_append(Zone, spot->borne);
    }
    spot = spot->next;
  }
  if (borne_list_length(Zone) == 0) {
    return creationZone(actual, ending, p - 0.1, usedCar, allListsBorne, Zone,
                        path); // if the zone is empty, we call the function
                               // with a lower p to increase the radius
  }
  return 0;
}

// returns the travel time between two bornes in minutes
int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual) {
  int time = 0;
  int travelDistance = distance(
      borneActual->latitude, borneActual->longitude, borneC->latitude,
      borneC->longitude); // calculates the travl distance between the actual
                          // borne and the borne we want to go to
  time = MIN(
      maxTimeCharging,
      60.0 * car->capacity *
          (car->autonomyUsable - (car->autonomyAct - (float)travelDistance)) /
          (float)(borneC->power *
                  car->autonomyMax)); // calculate the time to fully charge and
                                      // return it if it is lower than the
                                      // maxTimeCharging (or retrun
                                      // maxTimeCharging)
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
borne *updateBestBorne(borne *actual, borne *goal, borne *borneInTest,
                       double *bestTime, int *chargeTime, int *waitingTime,
                       int *travelTimeToGoal, int *travelTimeToBorneInTest,
                       int *bestPdcIndex, car *usedCar, int maxTimeCharging,
                       int maxTimeWaiting, int currentTime) {
  borne *temp = malloc(sizeof(borne));
  double timeToGoal = travelTime(borneInTest, goal);
  double timeToBorneInTest = travelTime(actual, borneInTest);
  int timeToChargeCar =
      timeToCharge(borneInTest, maxTimeCharging, usedCar, actual);
  int bestPdcIndexInTest = 0;
  int waitingTimeInTest = 0;
  // if the borne is not the goal borne, we calculate the waiting time and
  // actualise the parameters
  betterWaitTime(borneInTest, &waitingTimeInTest, &bestPdcIndexInTest,
                 &currentTime, &timeToChargeCar);
  if (timeToGoal + timeToBorneInTest + timeToChargeCar + waitingTimeInTest <=
          *travelTimeToGoal + *travelTimeToBorneInTest + *chargeTime +
              *waitingTime && // if time to charge + wait + drive is lower than
                              // the actual best time
      waitingTimeInTest <=
          maxTimeWaiting) { // and if the waiting time is
                            // lower than the max waiting time authorized
    // update the best borne and actualize the parameters
    temp = borneInTest;
    *bestTime =
        timeToGoal + timeToBorneInTest + timeToChargeCar + waitingTimeInTest;
    *chargeTime = timeToChargeCar;
    *waitingTime = waitingTimeInTest;
    *travelTimeToGoal = timeToGoal;
    *travelTimeToBorneInTest = timeToBorneInTest;
    *bestPdcIndex = bestPdcIndexInTest;
    return temp;
  }
  return NULL;
}

// returns the best borne to go to according to the goal borne and the actual in
// a zone
borne *findBestInZone(borne_list *Zone, borne *actual, borne *goal,
                      car *usedCar, double *bestTime, int *actualTime,
                      int *waitingTime, int *travelTimeToGoal,
                      int *travelTimeToBorneInTest, int *chargeTime,
                      int *maxTimeCharging, int *maxTimeWaiting,
                      int *bestPdcIndex) {
                        borne * temp = malloc(sizeof(borne));
  int n = borne_list_length(Zone);
  borne_list *spot = Zone;

  // we test every borne of the zone if is better than the best borne
  for (int i = 0; i < n; i++) {
    borne *borneInTest = borne_list_getBorne(spot);

    borne *test = updateBestBorne(
        actual, goal, borneInTest, bestTime, chargeTime, waitingTime,
        travelTimeToGoal, travelTimeToBorneInTest, bestPdcIndex, usedCar,
        *maxTimeCharging, *maxTimeWaiting, *actualTime);
    if (test != NULL) {
      temp = test;
    }
    spot = spot->next;
  }
  return temp;
}

// find the best path to go to the goal borne from the actual borne
// add to pathTime (actualTime, actualTime) in app
int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path,
                horaire_list *pathTime, borne_list *allListsBorne,
                int maxTimeWaiting, int maxTimeCharging, int *actualTime) {
  // add the actual borne to the path
  printf("11111 \n");
  debug_merde(allListsBorne);
  borne_list_append(path, actual);
  printf("actual : ");
  borne_print(actual);

  horaire_list_print(
      borne_list_getBorneById(allListsBorne, 1761)->horairePdc[0]);
  printf("2222222\n");
  debug_merde(allListsBorne);
  printf("yes\n");
  if (distance(actual->latitude, actual->longitude, ending->latitude,
               ending->longitude) <= usedCar->autonomyAct) {
    // if ending borne is reachable from actual, add ending to path and the
    // arrival time to the horaire_list and end the pathFinding
    borne_list_append(path, ending);
    horaire_list_append(
        pathTime,
        horaire_createWithValues(*actualTime + travelTime(actual, ending),
                                 *actualTime + travelTime(actual, ending)));
    return 0;
  } else {
    borne_list *Zone = borne_list_create();
    creationZone(actual, ending, 1, usedCar, allListsBorne, Zone, path);
    printf("3333333\n");
    debug_merde(allListsBorne);
    // find a zone to find the best
    if (borne_list_length(Zone) == 0) { // if the zone is empty, no borne is
                                        // reachable and the patj is impossible
      return 1;
    }
    
    // Each time, if the goal is unreachable it means we initialize the travel
    // time to the goal to unspeakable values and also the waiting time to be
    // sure we will find better
    // Please not tha the first borne is also tested in the function

    double bestTime = (float)INT32_MAX;
    int waitingTime = INT32_MAX / 8;
    int travelTimeToGoal = INT32_MAX / 8;

    int travelTimeToBorneInTest = INT32_MAX / 8;
    int chargeTime = INT32_MAX / 8;
    int bestPdcIndex = 0;
    // find the best in the zone
    borne* best = findBestInZone(Zone, actual, ending, usedCar, &bestTime, actualTime,
                   &waitingTime, &travelTimeToGoal, &travelTimeToBorneInTest,
                   &chargeTime, &maxTimeCharging, &maxTimeWaiting,
                   &bestPdcIndex);
    printf("4444444\n");
    debug_merde(allListsBorne);
    // add to pathTime arrivalTime and departureTime at the best borne

    horaire_list_append(
        pathTime,
        horaire_createWithValues(*actualTime + travelTimeToBorneInTest,
                                 *actualTime + bestTime - travelTimeToGoal));
    // add (to the right position) the "horaire" were the charging point is used
    // to the borne informations
    horaire_list_insert(best->horairePdc[bestPdcIndex],
                        horaire_createWithValues(
                            *actualTime + travelTimeToBorneInTest + waitingTime,
                            *actualTime + bestTime - travelTimeToGoal));
    printf("bestPdcIndex : %d\n", bestPdcIndex);
    horaire_list_print(best->horairePdc[bestPdcIndex]);
    horaire_list_print(best->horairePdc[bestPdcIndex]->next);
    horaire_list_print(best->horairePdc[bestPdcIndex]->prev);
    // Update the actual time to the departure time from best (after waiting and
    // charging)
    *actualTime += (int)bestTime - travelTimeToGoal;
    return pathFinding(
        usedCar, best, ending, path, pathTime, allListsBorne, maxTimeWaiting,
        maxTimeCharging,
        actualTime); // Find the path from the best (which is th enew actual/
                     // departure) to the destination
  }
}
