#include "../include/time_wait.h"
#include <stdint.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void getWaitingTimeAndPotentialChargeTime(horaire_list *list, int *waitingTime,
                                          int *possibleBetterPdcIndex,
                                          int *currentTime, int *chargeTime) {
  if (horaire_list_length(list) == 0) {
    waitingTime = 0;
    return;
  }
  horaire_list *temp = list;
  for (int i = 0; i < horaire_list_length(list); i++) {
    int DU = temp->horaire->heure_arrivee;
    if (DU > *(currentTime)) {
      int FU = temp->prev->horaire->heure_depart;
      if (FU > DU) {
        FU = *(currentTime);
      }
      if (DU - *(currentTime) >= *(chargeTime) &&
          *(waitingTime) >
              MAX((*currentTime), DU) - *(currentTime) + *(chargeTime)) {
        *(possibleBetterPdcIndex) = i;
        *(waitingTime) =
            MAX((*currentTime), DU) - *(currentTime) + *(chargeTime);
        return;
      }
    }
  };
}

bool betterWaitTime(borne *borne, int *watingTimeAct,
                    int *possibleBetterPdcIndex, int *currentTime,
                    int *chargeTime) {
  int waitingTime = INT16_MAX;
  for (int i = 0; i < borne->pdc; i++) {
    getWaitingTimeAndPotentialChargeTime(borne->horaires_pdc[i], &waitingTime,
                                         possibleBetterPdcIndex, currentTime,
                                         chargeTime);
  }
  bool b = waitingTime < *(watingTimeAct);
  if (b) {
    *(watingTimeAct) = waitingTime;
  }
  return b;
}
