#include "../include/car_list.h"
#include "../include/borne_list.h"

void findBestInZone(borne_list *Zone, borne *actual, borne *goal, int maxTimeCharging, int maxTimeWaiting, borne *best, double bestTime);

bool isBorneBetterThanCurrentBestBorne(int bestTime, borne *borneInTest, borne *actual, borne *goal, car *car, int maxTimeWaiting, int maxTimeCharging);

int travelTime(borne *actual, borne *goal, borne* borneInTest, car *car, int maxTimeCharging, int maxTimeWaiting);

int timeToCharge(borne *borne, int maxTimeCharging, car *car);