#include "line.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 14759

#ifndef CSV_IMPORT_H

#define CSV_IMPORT_H

struct csv_import {
  int size;
  line **line;
};

typedef struct csv_import csv_import;

// Functions

// Creation functions

csv_import *csv_import_create(int sizeOfArray, int sizeOfLine);

// Destroy functions

void csv_import_destroy(csv_import *file);

// Size functions

int csv_import_getSize(csv_import *file);

#endif
