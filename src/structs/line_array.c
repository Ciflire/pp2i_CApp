#include "../include/line_array.h"

line_array *line_array_create(int sizeOfArray, int sizeOfLine) {
  line_array *file = malloc(sizeof(line_array));
  file->size = sizeOfArray;
  file->line = calloc(sizeOfArray, sizeof(line));
  for (int i = 0; i < sizeOfArray; i++) {
    file->line[i] = line_create(sizeOfLine);
  }
  return file;
}

void line_array_destroy(line_array *file) {
  for (int i = 0; i < file->size; i++) {
    line_destroy(file->line[i]);
  }
  free(file->line);
  free(file);
}

int line_array_getSize(line_array *file) { return file->size; }

void line_array_print(line_array *file) {
  for (int i = 0; i < file->size; i++) {
    line_print(file->line[i]);
  }
}
