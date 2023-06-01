#include "include/path.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int path(itineraire_array *itineraires, unsigned int *seed,
         vehicule_list *list_of_all_vehicules,
         bornes_list *list_de_toutes_les_bornes, bornes_graph *bg,
         int *index_of_itineraire) {
  srand(*seed);
  *seed = rand();

  // init variables
  int car_id = 280;
  int id_origin = rand() % NB_BORNES + 1;
  int id_destination = rand() % NB_BORNES + 1;
  int battery_minimum = rand() % BATTERY_MINIMUM;
  int max_time_charging = rand() % MAX_TIME_CHARGING;
  int max_time_waiting = rand() % MAX_TIME_WAITING;
  int departure_time = rand() % 720;
  printf("car_id : %d\n", car_id);
  printf("id_origin : %d\n", id_origin);
  printf("id_destination : %d\n", id_destination);
  printf("battery_minimum : %d\n", battery_minimum);
  printf("max_time_charging : %d\n", max_time_charging);
  printf("max_time_waiting : %d\n", max_time_waiting);
  printf("departure_time : %d\n", departure_time);

  // get car name from user and get autonomie from csv



  // get vehicule, origin and destination
  vehicule *v = get_vehicule_by_id(list_of_all_vehicules, car_id);
  borne *origin = get_borne_by_id(list_de_toutes_les_bornes, id_origin);
  borne *destination = get_borne_by_id(list_de_toutes_les_bornes, id_destination);
  if (test_if_args_null(v, origin, destination)) {
    return 1;
  }
  int actual_time = departure_time;
  bornes_list *chemin = create_bornes_list();
  horaire_list *horaires = horaire_list_create();
  // get the path
  pathFinding(chemin, horaires, bg, origin, destination, battery_minimum,
              max_time_charging, max_time_waiting, actual_time, v, itineraires);
  if (chemin == NULL) {
    printf("No path found\n");
    destroy_vehicule_list(list_of_all_vehicules);
    return 1;
  }
  itineraires->array[*index_of_itineraire]->chemin = chemin;
  itineraires->array[*index_of_itineraire]->horaires = horaires;
  printf("path found : \n");
  print_bornes_list(chemin);
  return 0;
}

int pathFinding(bornes_list *path, horaire_list *horaires, bornes_graph *bg,
                borne *origin, borne *destination, int battery_minimum,
                int max_time_charging, int max_time_waiting, int actual_time,
                vehicule *v, itineraire_array *itineraires) {
  //  printf("in pathfinding...\n");
  add_borne(path, origin);
  add_horaire(horaires, actual_time, actual_time);
  borne *current_borne = origin;
  int current_borne_id = current_borne->id;
  int autonomie = v->autonomie;
  int charge = autonomie;

  while (!is_borne_in_list(path, destination->id)) {
    //    printf("actual path:\n");
    bornes_list *list_of_neighbours = bg->bornes_graph[current_borne_id];
    //    printf("getting_nearest_neighbour\n");
    borne *nearest_neighbour = get_borne(list_of_neighbours, 1);
    int *waiting_time_at_nearest_neighbour = 0;
    int a = get_waiting_time(itineraires, actual_time, nearest_neighbour);
    waiting_time_at_nearest_neighbour = &a;
    //    printf("nearest neighbour adress: %p\n", (void *)&nearest_neighbour);
    // Teste pour tous les voisins du point actuel s'il est meilleur que le
    // meilleur actuel (nearest_neighbour)
    for (int i = 0; i < get_length(list_of_neighbours); i++) {
      borne *current_neighbour_i = get_borne(list_of_neighbours, i);
      if (!is_borne_in_list(path, current_neighbour_i->id)) {
        /* if (current_neighbour_i->id == 1){
        printf("path: \n");
        print_bornes_list(path);
      } */
        /* if (destination->id == current_neighbour_i->id) {
          add_borne(path, current_neighbour_i);
          add_horaire(horaires, actual_time, actual_time);
          return 0;
        } */
        if (test_condition(current_borne, current_neighbour_i, destination,
                           nearest_neighbour, charge, battery_minimum,
                           max_time_waiting, actual_time, v, max_time_charging,
                           waiting_time_at_nearest_neighbour, itineraires)) {
          nearest_neighbour = current_neighbour_i;
        }
      }
    }
    //
    add_borne(path, nearest_neighbour);
    int arr_time =
        actual_time + (int)(get_distance_x_y(current_borne, nearest_neighbour) *
                            60.0 / 130.0);
    actual_time = arr_time +
                  get_charging_time(nearest_neighbour, v, max_time_charging) +
                  *waiting_time_at_nearest_neighbour;
    add_horaire(horaires, arr_time, actual_time);
    current_borne = nearest_neighbour;
    current_borne_id = current_borne->id;
    // mets a jour la charge du vehicule à la borne actuelle
    if (get_charging_time(nearest_neighbour, v, max_time_charging) !=
        max_time_charging) {
      charge = autonomie;
    } else {
      charge = charge - get_distance_x_y(current_borne, nearest_neighbour) +
               (int)((float)max_time_charging /
                     get_charging_time(nearest_neighbour, v, 999999)) *
                   (float)autonomie;
    }
    // actual_time = actual_time + dist_current_nearest_neighbour*60/130;
  }
  destroy_borne(current_borne);
  return 0;
}

bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum, int max_time_waiting, int actual_time,
                    vehicule *v, int max_time_charging,
                    int *wait_time_at_nearest_neighbour,
                    itineraire_array *itineraires) {
  int dist_current_i = get_distance_x_y(current_borne, current_neighbour_i);
  // printf("dist_current_i: %d\n", dist_current_i);
  int dist_i_final = get_distance_x_y(current_neighbour_i, destination);
  // printf("dist_i_final: %d\n", dist_i_final);
  int dist_current_nearest_neighbour =
      get_distance_x_y(current_borne, nearest_neighbour);
  /* printf("dist_current_nearest_neighbour: %d\n",
         dist_current_nearest_neighbour); */
  int dist_nearest_neighbour_final =
      get_distance_x_y(nearest_neighbour, destination);
  // printf("dist_nearest_neighbour_final: %d\n", dist_nearest_neighbour_final);
  int wait_time = 0;
  wait_time = get_waiting_time(
      itineraires,
      actual_time +
          get_distance_x_y(current_borne, nearest_neighbour) * 60 / 130,
      nearest_neighbour);
  int max_charging_time_i =
      get_charging_time(current_neighbour_i, v, max_time_charging);
  // printf("max_charging_time_i: %d\n", max_charging_time_i);

  int max_charging_time_nearest_neighbour =
      get_charging_time(nearest_neighbour, v, max_time_charging);
  /* printf("max_charging_time_nearest_neighbour: %d\n",
         max_charging_time_nearest_neighbour); */

  // b1 test si le temps de trajet en passant par le voisin i+chargemeent et
  // attente en i est plus court que le temps de trajet en passant par l'actuel
  // meilleur+chargement et attente en l'actuel meilleur
  bool b1 = ((float)dist_current_i * (float)60 / (float)130 + (float)wait_time +
             (float)max_charging_time_i +
             (float)dist_i_final * (float)60 / (float)130) <
            ((float)dist_current_nearest_neighbour * (float)60 / (float)130 +
             (float)*wait_time_at_nearest_neighbour +
             (float)max_charging_time_nearest_neighbour +
             (float)dist_nearest_neighbour_final * (float)60 / (float)130);
  // b2
  bool b2 = charge - dist_current_i >=
            (float)v->autonomie * (float)battery_minimum /
                (float)100; // on vérifie s'il est pas trop loin
  // b3
  bool b3 = wait_time <= max_time_waiting;
  bool b4 = destination->id == current_neighbour_i->id;
  /* printf("b1: %d\n", b1);
  printf("b2: %d\n", b2);
  printf("b3: %d\n", b3);
   */
  if ((b1 && b2 && b3) || (b4 && b2)) {
    *wait_time_at_nearest_neighbour = wait_time;
  }
  return (b1 && b2 && b3) || (b4 && b2);
}

//teste si les arguments sont null et détruit les arguments si c'est le cas
bool test_if_args_null(vehicule *v, borne *depart, borne *arrivee) {
  if (v == NULL) {
    printf("Le vehicule n'existe pas\n");
    destroy_vehicule(v);
    return true;
  } else if (depart == NULL) {
    printf("La borne de depart n'existe pas\n");
    destroy_vehicule(v);
    destroy_borne(depart);
    return true;
  } else if (arrivee == NULL) {
    printf("La borne d'arrivee n'existe pas\n");
    destroy_vehicule(v);
    destroy_borne(depart);
    destroy_borne(arrivee);
    return true;
  }
  return false;
}
