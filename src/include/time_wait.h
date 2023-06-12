#include "borne_list.h"
#include "horaire_list.h"

#ifndef TIME_WAIT_H

#define TIME_WAIT_H

void getWaitingTimeAndPotentialChargeTime(horaire_list *list, int *waitingTime,
                                          int *possibleBetterPdcIndex,
                                          int *currentTime, int *chargeTime);

bool betterWaitTime(borne *borne, int *watingTimeAct, int *betterPdcIndex,
                    int *currentTime, int *chargeTime);

#endif
