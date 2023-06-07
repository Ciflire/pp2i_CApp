#include "../include/csv_import.h"

void *csv_import_create(int sizeOfArray, int sizeOfLine, csv_import *file) {
  file->size = sizeOfArray;
  file->info = malloc(sizeof(line *) * sizeOfArray);
  for (int i = 0; i < sizeOfArray; i++) {
    file->info[i] = line_create(sizeOfLine);
  }
  return file;
}

void csv_import_destroy(csv_import *file) {
  for (int i = 0; i < file->size; i++) {
    line_destroy(file->info[i]);
  }
  free(file->info);
  free(file);
}

int csv_import_getSize(csv_import *file) { return file->size; }
