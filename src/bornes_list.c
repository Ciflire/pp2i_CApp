#include "include/bornes_list.h"

bornes_list *create_bornes_list(void) {
  bornes_list *bl = malloc(sizeof(bornes_list));
  bl->index = 0;
  bl->next = NULL;
  bl->prev = NULL;
  return bl;
}

void destroy_bornes_list(bornes_list *bl) {
  int length = get_length(bl);
  if (length == 0) {
    free(bl);
    return;
  }
  for (int i = 0; i < length; i++) {
    bornes_list *next = bl->next;
    destroy_borne(bl->borne);
    free(bl);
    bl = next;
  }
}

void add_borne(bornes_list *bl, borne *b) {
  if (bl->index == 0) {
    bl->index = 1;
    bl->next = bl;
    bl->prev = bl;
    bl->borne = b;
  } else {
    bornes_list *new_bl = malloc(sizeof(bornes_list));
    new_bl->index = get_length(bl) + 1;
    new_bl->prev = bl->prev;
    new_bl->next = bl;
    bl->prev->next = new_bl;
    bl->prev = new_bl;
    new_bl->borne = b;
  }
}

int get_length(bornes_list *bl) {
  if (bl->index == 0) {
    return 0;
  } else {
    return bl->prev->index;
  }
}

borne *get_borne(bornes_list *bl, int index) {
  if (index > get_length(bl)) {
    return NULL;
  } else {
    bornes_list *current = bl;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->borne;
  }
}

bool is_borne_in_list(bornes_list *bl, int id) {
  if (bl->index == 0) {
    return false;
  } else {
    bornes_list *current = bl;
    for (int i = 0; i < get_length(bl); i++) {
      if (current->borne->id == id) {
        return true;
      }
      current = current->next;
    }
    return false;
  }
}

borne *get_borne_by_id(bornes_list *bl, int id) {
  if (bl->index == 0) {
    return NULL;
  } else {
    bornes_list *current = bl;
    for (int i = 0; i < get_length(bl); i++) {
      if (current->borne->id == id) {
        return current->borne;
      }
      current = current->next;
    }
    return NULL;
  }
}
