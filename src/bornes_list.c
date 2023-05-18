#include "bornes_list.h"

bornes_list *create_bornes_list(void) {
  bornes_list *bl = malloc(sizeof(bornes_list));
  bl->size = 0;
  bl->next = NULL;
  return bl;
}

void destroy_bornes_list(bornes_list *bl) {
  bornes_list *next = bl->next;
  while (next != NULL) {
    bornes_list *tmp = next->next;
    destroy_borne(next->borne);
    free(next);
    next = tmp;
  }
  free(bl);
}
