#include "../include/borne_list.h"

// Creates a borne_list
borne_list *borne_list_create(void) {
  borne_list *list = malloc(sizeof(borne_list));
  list->prev = list;
  list->next = list;
  list->borne = NULL;
  list->index = 0;
  return list;
}

// Destroys a borne_list
void borne_list_destroy(borne_list *list) {
  borne_list *temp = list->next;
  if (borne_list_length(list->prev) == 0) {
    free(list);
    return;
  }
  if (borne_list_length(list) == 1) {
    borne_destroy(list->borne);
    free(list);
    return;
  }
  horaire_list_print(borne_list_getBorneById(temp, 1575)->horairePdc[0]);
  for (int i = 0; i < borne_list_length(list); i++) {
    /* printf("i = %d\n", i);
    printf("in destroy borne : ");
    horaire_list_print(
        borne_list_getBorneById(temp, 1761)->horairePdc[0]);
    printf("yes\n"); */
    temp = temp->next;
    horaire_list_print(temp->prev->borne->horairePdc[0]);
    borne_destroy(temp->prev->borne);
    free(temp->prev);
  }
  borne_destroy(temp->borne);
  free(temp);
  return;
}

// Get the index of a borne in a list
int borne_list_getIndex(borne_list *list) { return list->index; }

// Gets the previous borne_list
borne *borne_list_getBorne(borne_list *list) { return list->borne; }

// Gets the next borne_list
borne_list *borne_list_getNext(borne_list *list) { return list->next; }

// Get the previous borne in a list
borne_list *borne_list_getPrev(borne_list *list) { return list->prev; }

// Appends a borne to a borne_list
void borne_list_append(borne_list *list, borne *borne) {
  if (borne_list_length(list) == 0) {
    list->borne = borne;
    list->index = 1;
    return;
  }
  borne_list *b_l_new = borne_list_create();
  b_l_new->index = borne_list_length(list) + 1;
  b_l_new->borne = borne;
  b_l_new->next = list;
  b_l_new->prev = list->prev;
  list->prev = b_l_new;
  b_l_new->prev->next = b_l_new;
  return;
}

// Gets the length of a borne_list
int borne_list_length(borne_list *list) { return list->prev->index; }

// Tells if a borne is in a borne_list
bool borne_list_isBorneInList(borne_list *list, borne *borne) {
  if (borne_list_length(list) == 0) {
    return false;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    if (borne_equals(temp->borne, borne)) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

// Removes a borne from a borne_list
borne *borne_list_getBorneById(borne_list *list, int id) {
  if (borne_list_length(list) == 0) {
    return NULL;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    if (id == 1576 && temp->borne->id >1500 && temp->borne->id<1600) {
      printf("id : %d\n", temp->borne->id);
    }
    if (temp->borne->id == id) {
      return borne_list_getBorne(temp);
    }
    temp = temp->next;
  }
  return NULL;
}

// Removes a borne from a borne_list
void borne_list_print(borne_list *list) {
  if (borne_list_length(list) == 0) {
    return;
  }
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    printf("Borne %d :\n", temp->index);
    borne_print(temp->borne);
    temp = temp->next;
  }
  return;
}

// Removes a borne from a borne_list
void borne_list_printPathLink(borne_list *list) {
  char *url = "https://www.google.com/maps/dir/";
  if (borne_list_length(list) == 0) {
    return;
  }
  borne_list *temp = list;
  printf("%s", url);
  for (int i = 0; i < borne_list_length(list); i++) {
    printf("'%lf,%lf'/", temp->borne->latitude, temp->borne->longitude);
    temp = temp->next;
  }
  printf("\n");
}

// Prints a url to print a path in Maps integrator
void borne_list_printPathMapsIntegrator(borne_list *list) {
  FILE *f = fopen("response_link.txt", "w");
  printf(
      "https://www.google.com/maps/embed/v1/"
      "directions?key=AIzaSyAsCiKsNXq95zuQsLyf09ZcoxdQZPzTMbo&origin=%lf,%lf",
      list->borne->latitude, list->borne->longitude);
  fprintf(
      f,
      "https://www.google.com/maps/embed/v1/"
      "directions?key=AIzaSyAsCiKsNXq95zuQsLyf09ZcoxdQZPzTMbo&origin=%lf,%lf",
      list->borne->latitude, list->borne->longitude);
  if (borne_list_length(list) == 2) {
    printf("&destination=%lf,%lf", list->next->borne->latitude,
           list->next->borne->longitude);
    fprintf(f, "&destination=%lf,%lf", list->next->borne->latitude,
            list->next->borne->longitude);
  } else {
    printf("&waypoints=");
    fprintf(f, "&waypoints=");
    borne_list *temp = list->next;
    for (int i = 0; i < borne_list_length(list) - 2; i++) {
      if (i != 0) {
        printf("|");
        fprintf(f, "|");
      }
      printf("%lf,%lf", temp->borne->latitude, temp->borne->longitude);
      fprintf(f, "%lf,%lf", temp->borne->latitude, temp->borne->longitude);
      temp = temp->next;
    }
    printf("&destination=%lf,%lf", list->next->borne->latitude,
           list->next->borne->longitude);
    fprintf(f, "&destination=%lf,%lf", list->next->borne->latitude,
            list->next->borne->longitude);
  }
  printf("&mode=driving&units=metric\n");
  fprintf(f, "&mode=driving&units=metric\n");
  fclose(f);
}

void borne_list_savePathInPythonListFormat(borne_list *list, char *filename) {
  FILE *f = fopen(filename, "a");
  fprintf(f, "[");
  borne_list *temp = list;
  for (int i = 0; i < borne_list_length(list); i++) {
    if (i != 0) {
      fprintf(f, ",");
    }
    fprintf(f, "%d", temp->borne->id);
    temp = temp->next;
  }
  fprintf(f, "]\n");
  fclose(f);
}

