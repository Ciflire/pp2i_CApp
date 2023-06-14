#include "borne_list.h"
#include "horaire_list.h"

#ifndef TIME_WAIT_H

#define TIME_WAIT_H

// Get the waiting time and the potential charge time of a car
void getWaitingTimeAndPotentialChargeTime(horaire_list *list, int *waitingTime,
                                          int *possibleBetterPdcIndex,
                                          int *currentTime, int *chargeTime);

// Get the waiting time of a car
bool betterWaitTime(borne *borne, int *watingTimeAct, int *betterPdcIndex,
                    int *currentTime, int *chargeTime);

#endif
