#include "../include/car_list.h"
#include "../include/borne_list.h"

int distance(double xDep, double yDep, double xArr, double yArr);

int creationZone(borne *actual, borne *ending, double p, car *usedCar, borne_list *allListsBorne, borne_list *Zone);

int pathFinding(car *usedCar, borne *actual, borne *ending, borne_list *path, borne_list *allListsBorne, int maxTimeWaiting);

void findBestInZone(borne_list *Zone, borne *actual, borne *goal, int maxTimeCharging, int maxTimeWaiting, borne *best, double bestTime);

bool isBorneBetterThanCurrentBestBorne(int bestTime, borne *borneInTest, borne *actual, borne *goal, car *car, int maxTimeWaiting, int maxTimeCharging);

int travelTime(borne *actual, borne *goal, borne* borneInTest, car *car, int maxTimeCharging, int maxTimeWaiting);

int timeToCharge(borne *borne, int maxTimeCharging, car *car);