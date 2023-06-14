#include "../include/line_array.h"

csv_import *csv_import_create(int sizeOfArray, int sizeOfLine) {
  csv_import *file = malloc(sizeof(csv_import));
  file->size = sizeOfArray;
  file->line = calloc(sizeOfArray, sizeof(line));
  for (int i = 0; i < sizeOfArray; i++) {
    file->line[i] = line_create(sizeOfLine);
  }
  return file;
}

void csv_import_destroy(csv_import *file) {
  for (int i = 0; i < file->size; i++) {
    line_destroy(file->line[i]);
  }
  free(file->line);
  free(file);
}

int csv_import_getSize(csv_import *file) { return file->size; }

void csv_import_print(csv_import *file) {
  for (int i = 0; i < file->size; i++) {
    line_print(file->line[i]);
  }
}
