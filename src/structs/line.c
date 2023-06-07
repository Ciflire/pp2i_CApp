#include "../include/line.h"

line *line_create(int size) {
  line *l = malloc(sizeof(line));
  l->size = size;
  l->info = malloc(sizeof(char *) * size);
  for (int i = 0; i < size; i++) {
    l->info[i] = malloc(sizeof(char) * MAX_STR_LEN);
  }
  return l;
}

void line_destroy(line *l) {
  for (int i = 0; i < l->size; i++) {
    free(l->info[i]);
  }
  free(l->info);
  free(l);
}

int line_getSize(line *l) { return l->size; }