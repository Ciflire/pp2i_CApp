#include "line.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES_BORNES 14759
#define MAX_LINES_CARS 287

#ifndef line_array_H

#define line_array_H

struct line_array {
  int size;
  line **line;
};

typedef struct line_array line_array;

// Functions

// Creation functions

line_array *line_array_create(int sizeOfArray, int sizeOfLine);

// Destroy functions

void line_array_destroy(line_array *file);

// Size functions

int line_array_getSize(line_array *file);

// print functions

void line_array_print(line_array *file);

#endif
