#include "../include/time_wait.h"
#include <stdint.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void getWaitingTimeAndPotentialChargeTime(horaire_list *list, int *waitingTime,
                                          int *possibleBetterPdcIndex,
                                          int *currentTime, int *chargeTime) {
  // If list is empty, there is no waiting time
  if (horaire_list_length(list) == 0) {
    *waitingTime = 0;

    return;
  }

  horaire_list *temp = list; // create temporary pointer to horaire_list

  for (int i = 0; i < horaire_list_length(list); i++) {
    int usageStart =
        temp->horaire
            ->heure_arrivee; // Retreives arrival time at borne for usage i
    // if the next usage is after the car arrival then
    if (usageStart > *currentTime) {
      int usageEnd =
          temp->prev->horaire
              ->heure_depart; // get the previous car's departure time
      // ensures we have not looped to the end of the horaire_list
      if (usageEnd > usageStart) {
        usageEnd = *currentTime;
      }
      // checks if there is enough time to charge and that it's the shortest
      // waiting time before charge
      if (usageStart - *(currentTime) >= *chargeTime &&
          *waitingTime >
              MAX(*currentTime, usageStart) - *currentTime + *chargeTime) {
        // if it's the case, set the pdc to the currrent tested and the waiting
        // time associated
        *possibleBetterPdcIndex = i;
        *waitingTime =
            MAX(*currentTime, usageStart) - *(currentTime) + *(chargeTime);
        return;
      }
    }
  };
}

bool betterWaitTime(borne *borne, int *watingTimeAct, int *betterPdcIndex,
                    int *currentTime, int *chargeTime) {
  int waitingTime = INT16_MAX;
  for (int i = 0; i < borne->pdc; i++) {
    getWaitingTimeAndPotentialChargeTime(borne->horaires_pdc[i], &waitingTime,
                                         betterPdcIndex, currentTime,
                                         chargeTime);
    if (waitingTime == 0) {
      *betterPdcIndex = i;
    }
  }
  bool b = waitingTime < *watingTimeAct;
  if (b) {
    *watingTimeAct = waitingTime;
    // printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  }
  return b;
}
