#include "../include/car_list.h"
#include "../include/borne_list.h"
#include "../include/horaire_list.h"
#include "../include/time_wait.h"


int distance(double xDep, double yDep, double xArr, double yArr);

int creationZone(borne *actual, borne *ending, double p, car *usedCar, borne_list *allListsBorne, borne_list *Zone);

int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path, horaire_list *pathTime,
                borne_list *allListsBorne, int maxTimeWaiting,
                int maxTimeCharging, int *actualTime);

void findBestInZone(borne_list *Zone, borne *actual, borne *goal, car *usedCar,
                    borne *best, double *bestTime, int *actualTime,
                    int *waitingTime, int *travelTimeToGoal,
                    int *travelTimeToBorneInTest, int *chargeTime,
                    int *maxTimeCharging);

void isBorneBetterThanCurrentBestBorne(borne *best, double *bestTime,
                                       borne *borneInTest, borne *actual,
                                       borne *goal, int *bestPdcIndex,
                                       int *chargeTime, int *waitingTime,
                                       int *actualTime, int *travelTimeToGoal,
                                       int *travelTimeToBorneInTest,
                                       int *maxTimeCharging, car *car);

double travelTime(borne *actual, borne *goal);

int timeToCharge(borne *borneC, int maxTimeCharging, car *car,
                 borne *borneActual);
