#include "../include/line.h"

// Init the structure for a given size (here 3 for cars, 4 for borne)
// Remember t define the MAX_STR_LEN in the header (default 256)
line *line_create(int size) {
  line *l = malloc(sizeof(line));
  l->size = size;
  l->info = malloc(sizeof(char *) * size);
  for (int i = 0; i < size; i++) {
    l->info[i] = malloc(sizeof(char) * MAX_STR_LEN);
  }
  return l;
}

// Destroy a line
void line_destroy(line *l) {
  for (int i = 0; i < l->size; i++) {
    free(l->info[i]);
  }
  free(l->info);
  free(l);
}

// Gets the size of a line
int line_getSize(line *l) { return l->size; }

// Prints a line
void line_print(line *l) {
  for (int i = 0; i < line_getSize(l); i++) {
    printf("%s ", l->info[i]);
  }
  printf("\n");
}
