#include "../include/borne_list.h"
#include "../include/horaire_list.h"

void getWaitingTimeAndPotentialChargeTime(horaire_list *horaire_list_pdc,
                                          int *waitingTime,
                                          int *possibleBetterPdcIndex,
                                          int *currentTime, int *chargeTime);

bool betterWaitTime(borne *borne, int *watingTimeAct,
                    int *possibleBetterPdcIndex, int *currentTime,
                    int *chargeTime);