#include "include/utils_dijkstra.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define M_PI 3.14159265358979323846

int get_distance_x_y(borne *bDep, borne *bArr) {
  return (int)sqrt(pow(bArr->xpos - bDep->xpos, 2) +
                   pow(bArr->ypos - bDep->ypos, 2));

  /* double R = 6371;
  double varLong = (bArr->xpos - bDep->xpos) * M_PI / 180;
  double varLat = (bArr->ypos - bDep->ypos) * M_PI / 180;
  double a = sin(varLat / 2) * sin(varLat / 2) +
             cos(bDep->ypos * M_PI / 180) * cos(bArr->ypos * M_PI / 180) *
                 sin(varLong / 2) * sin(varLong / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int d = (int)R * c;
  return d;*/
}

int get_charging_time(borne *b, vehicule *v, int max_time_charging) {
  return MIN((int)((float)v->capacity / (float)b->power) * 60.0,
             max_time_charging);
}

int get_waiting_time(itineraire_array *it_array, int arrival_time, borne *borne) {
  if (it_array->size == 0) {
    return 0;
  }
  int n_pdc = borne->qte;
  int index = 0;
  horaire_list *horaire_list_of_conflicts = horaire_list_create();

  for (int i = 0; i < it_array->size; i++) {
    index = get_borne_index_by_id(it_array->array[i]->chemin, borne->id);
    if (index != -1) {
      horaire_list *horaire_list_conflictuous =
          get_horaire(it_array->array[i]->horaires, index);
      if (horaire_list_conflictuous->heure_arrivee <= arrival_time &&
          horaire_list_conflictuous->heure_depart >= arrival_time) {
        add_horaire(horaire_list_of_conflicts,
                    horaire_list_conflictuous->heure_arrivee,
                    horaire_list_conflictuous->heure_depart);
      }
    }
  }
  int n_pdc_available = 0;
  int waiting_time = -1;
  while (n_pdc_available <= 0) {
    waiting_time++;
    n_pdc_available = n_pdc;
    horaire_list *current = horaire_list_of_conflicts;
    for (int i = 0; i < get_horaire_list_size(horaire_list_of_conflicts); i++) {
      if (current->heure_depart >= arrival_time + waiting_time &&
          current->heure_arrivee <= arrival_time + waiting_time) {
        n_pdc_available--;
      }
      current = current->next;
    }
  }
  return waiting_time;
}

