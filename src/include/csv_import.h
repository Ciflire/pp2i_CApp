#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 14760

#ifndef CSV_IMPORT_H

#define CSV_IMPORT_H

struct line {
  int size;
  char *args[];
};

typedef struct line line;

struct csv_import {
  int size;
  line **csv[];
};

typedef struct csv_import csv_import;

int csv_import_getSize(csv_import *file);

int line_getSize(line *l);
#endif