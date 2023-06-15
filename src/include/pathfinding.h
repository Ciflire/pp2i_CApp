#include "../include/borne_list.h"
#include "../include/car_list.h"
#include "../include/horaire_list.h"
#include "../include/time_wait.h"
#include <stdint.h>

#define M_PI 3.14159265358979323846

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// harversine distance in km
int distance(double xDep, double yDep, double xArr, double yArr);

// creates a zone around certain coordinates that the car can reach and that is
// not already in the path and different that the borne we are on if the zone is
// empty at the end, we call the function with a lower p until it gets negative
// and returns an error
int creationZone(borne *actual, borne *ending, double p, car *usedCar,
                 borne_list *allListsBorne, borne_list *Zone, borne_list *path);

// returns the travel time between two bornes in minutes
int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual);

// returns the travel time between two bornes in minutes
double travelTime(borne *actual, borne *goal);

// If the borneInTest is better than the bestBorne, we change the bestBorne and
// actualize the bestTime, charge time, waiting time, travelTimeToGoal,
// travelTimeToBorneInTest, and bestPdcIndex
borne * updateBestBorne(borne *actual, borne *goal, borne *borneInTest,
                     double *bestTime, int *chargeTime, int *waitingTime,
                     int *travelTimeToGoal, int *travelTimeToBorneInTest,
                     int *bestPdcIndex, car *usedCar, int maxTimeCharging,
                     int maxTimeWaiting, int currentTime);

// returns the best borne to go to according to the goal borne and the actual in
// a zone
borne *findBestInZone(borne_list *Zone, borne *actual, borne *goal, car *usedCar,
                    double *bestTime, int *actualTime,
                    int *waitingTime, int *travelTimeToGoal,
                    int *travelTimeToBorneInTest, int *chargeTime,
                    int *maxTimeCharging, int *maxTimeWaiting,
                    int *bestPdcIndex);

// find the best path to go to the goal borne from the actual borne
// add to pathTime (actualTime, actualTime) in app
int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path,
                horaire_list *pathTime, borne_list *allListsBorne,
                int maxTimeWaiting, int maxTimeCharging, int *actualTime);
