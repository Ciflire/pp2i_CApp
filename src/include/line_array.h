#include "line.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES_BORNES 14759
#define MAX_LINES_CARS 287

#ifndef line_array_H

#define line_array_H

// Define a structure for a line_array
struct line_array {
  int size;
  line **line;
};

// Define the type line_array : a list of lines
typedef struct line_array line_array;

// Creates a line_array
line_array *line_array_create(int sizeOfArray, int sizeOfLine);

// Destroys a line_array
void line_array_destroy(line_array *file);

// Get the size of a line_array
int line_array_getSize(line_array *file);

// Prints a line_array
void line_array_print(line_array *file);

#endif
