#include "include/path.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum,
                    int max_time_waiting, /*int actual_time,*/
                    vehicule *v, int max_time_charging);

bornes_list *pathFinding(bornes_graph *bg, borne *origin, borne *destination,
                         int battery_minimum, int max_time_charging,
                         int max_time_waiting, int *distances,
                         /*int actual_time, */ vehicule *v);
int main(void) {
  int car_id = 0;
  int *id_origin = 0;
  int *id_destination = 0;
  int *battery_minimum = 0;
  int *max_time_charging = 0;
  int *max_time_waiting = 0;
  int autonomie = 0;
  // get car name from user and get autonomie from csv
  printf("Give your car id:");
  scanf("%d", &car_id);
  vehicule_list *list_of_all_vehicules = create_vehicule_list();
  getCarInfos(list_of_all_vehicules);
  free(id_origin);

  vehicule *v = get_vehicule_by_id(list_of_all_vehicules, car_id);
  if (v == NULL) {
    printf("Car not found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    return (1);
  }
  // generate the graph
  bornes_list *list_de_toutes_les_bornes = create_bornes_list();
  int *distances = (int *)malloc(sizeof(int) * 184099266);
  printf("Generating graph...\n");
  printf("Autonomie: %d\n", v->autonomie);
  autonomie = v->autonomie;
  bornes_graph *bg =generate_graph_fromCSV(autonomie, list_de_toutes_les_bornes, distances);
  printf("Graph generated\n");
  if (bg == NULL) {
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    printf("Error while generating graph\n");
    return 1;
  }
  printf("Graph generated\n");
  // get id_origin and id_destination from user
  printf("Give your origin id:");
  scanf("%d", id_origin);
  if (*id_origin < 0) {
    printf("Origin id not found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    return (1);
  }
  borne *origin;
  origin = get_borne_by_id(list_de_toutes_les_bornes, *id_origin);
  if (origin == NULL) {
    printf("Origin id not found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    return (1);
  }

  printf("Give your destination id:");
  scanf("%d", id_destination);
  if (*id_destination < 0) {
    printf("Destination id not found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    return (1);
  }
  borne *destination;
  destination = get_borne_by_id(list_de_toutes_les_bornes, *id_destination);
  if (destination == NULL) {
    printf("Destination id not found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    destroy_borne(destination);
    return (1);
  }

  printf("Give your battery minimum (in percent):");
  scanf("%d", battery_minimum);
  if (*battery_minimum < 0 || *battery_minimum > 100) {
    printf("Battery minimum not well defined\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    destroy_borne(destination);
    return (1);
  }
  printf("Give your max time charging in minutes (99999 for infinite):");
  scanf("%d", max_time_charging);
  if (*max_time_charging < 0) {
    printf("Max time charging not well defined\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    destroy_borne(destination);
    return (1);
  }
  printf("Give your max time waiting in minutes (99999 for infinite):");
  scanf("%d", max_time_waiting);
  if (*max_time_waiting < 0) {
    printf("Max time waiting not well defined\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    destroy_bornes_list(list_de_toutes_les_bornes);
    destroy_bornes_graph(bg);
    free(distances);
    destroy_borne(origin);
    destroy_borne(destination);
    return (1);
  }

  // get the path
  // int actual_time = 0;
  bornes_list *chemin =
      pathFinding(bg, origin, destination, *battery_minimum, *max_time_charging,
                  *max_time_waiting, distances, /*actual_time,*/ v);
  if (chemin == NULL) {
    printf("No path found\n");
    free(id_destination);
    free(battery_minimum);
    free(max_time_charging);
    free(max_time_waiting);
    destroy_vehicule_list(list_of_all_vehicules);
    return 1;
  }
  // print the path
  print_bornes_list(chemin);
  free(id_destination);
  free(battery_minimum);
  free(max_time_charging);
  free(max_time_waiting);
  destroy_vehicule_list(list_of_all_vehicules);
  destroy_bornes_list(list_de_toutes_les_bornes);
  destroy_bornes_graph(bg);
  free(distances);
  destroy_borne(origin);
  destroy_borne(destination);
  return 0;
}

bornes_list *pathFinding(bornes_graph *bg, borne *origin, borne *destination,
                         int battery_minimum, int max_time_charging,
                         int max_time_waiting, int *distances,
                         /*int actual_time, */ vehicule *v) {
  bornes_list *path = create_bornes_list();
  add_borne(path, origin);
  borne *current_borne = origin;
  int current_borne_id = current_borne->id;
  int autonomie = v->autonomie;
  int charge = autonomie;
  while (!is_borne_in_list(path, destination->id)) {
    bornes_list *list_of_neighbours = bg->bornes_graph[current_borne_id];
    borne *nearest_neighbour = get_borne(list_of_neighbours, 0);
    int dist_current_nearest_neighbour =
        distances[index_of_distance(current_borne_id, nearest_neighbour->id)];
    for (int i = 0; i < get_length(list_of_neighbours); i++) {
      borne *current_neighbour_i = get_borne(list_of_neighbours, i);
      int dist_current_i = distances[index_of_distance(
          current_borne_id, current_neighbour_i->id)];
      if (test_condition(current_borne, current_neighbour_i, destination,
                         nearest_neighbour, charge, battery_minimum,
                         max_time_waiting, /*actual_time,*/ v,
                         max_time_charging)) {

        nearest_neighbour = current_neighbour_i;
        dist_current_nearest_neighbour = dist_current_i;
      }
    }
    add_borne(path, nearest_neighbour);
    current_borne = nearest_neighbour;
    current_borne_id = current_borne->id;
    if (get_charging_time(nearest_neighbour, v, max_time_charging) !=
        max_time_charging) {
      charge = autonomie;
    } else {
      charge = charge - dist_current_nearest_neighbour +
               (max_time_charging /
                get_charging_time(nearest_neighbour, v, 999999)) *
                   autonomie;
    }
    // actual_time = actual_time + dist_current_nearest_neighbour*60/130;
  }
  destroy_borne(current_borne);
  return path;
}

bool test_condition(borne *current_borne, borne *current_neighbour_i,
                    borne *destination, borne *nearest_neighbour, int charge,
                    int battery_minimum,
                    int max_time_waiting, /*int actual_time,*/
                    vehicule *v, int max_time_charging) {
  int dist_current_i = get_distance_x_y(current_borne, current_neighbour_i);
  int dist_i_final = get_distance_x_y(current_neighbour_i, destination);
  int dist_current_nearest_neighbour =
      get_distance_x_y(nearest_neighbour, current_borne);
  int dist_nearest_neighbour_final =
      get_distance_x_y(nearest_neighbour, destination);
  int wait_time = 0;
  // wait_time = get_wait_time(, actual_time);
  int max_charging_time_i =
      get_charging_time(current_neighbour_i, v, max_time_charging);
  int max_charging_time_nearest_neighbour =
      get_charging_time(nearest_neighbour, v, max_time_charging);
  return dist_current_i * 60 / 130 + wait_time +
                 max_charging_time_i * (1 - charge / v->autonomie) +
                 dist_i_final * 60 / 130 <
             dist_current_nearest_neighbour * 60 / 130 + wait_time +
                 max_charging_time_nearest_neighbour +
                 dist_nearest_neighbour_final * 60 / 130 &&
         charge - dist_current_i > v->autonomie * battery_minimum &&
         wait_time < max_time_waiting;
}
