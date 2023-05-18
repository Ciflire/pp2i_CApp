#include "bornes_list.h"

bornes_list *create_bornes_list(void) {
  bornes_list *bl = malloc(sizeof(bornes_list));
  bl->size = 0;
  bl->next = NULL;
  return bl;
}

void destroy_bornes_list(bornes_list *bl) {
  if (bl->next != NULL) {
    destroy_bornes_list(bl->next);
  }
  free(bl);
}

void add_borne(bornes_list *bl, borne *b) {
  if (bl->size == 0) {
    bl->borne = b;
    bl->size++;
    return;
  }
  while (bl->next != NULL) {
    bl->size++;
    bl = bl->next;
  }
  bl->next = create_bornes_list();
  bl->next->borne = b;
  bl->size++;
}
