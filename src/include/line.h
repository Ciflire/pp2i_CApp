#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 64

#ifndef LINE_H

#define LINE_H

// Define a structure for a line
struct line {
  int size;
  char **info;
};

// Define the type line : an array of Strings
typedef struct line line;

// Init the structure for a given size (here 3 for cars, 4 for borne)
// Remember t define the MAX_STR_LEN in the header (default 256)
line *line_create(int size);

// Destroy a line
void line_destroy(line *l);

// Get the size of a line
int line_getSize(line *l);

// Prints a line
void line_print(line *l);

#endif
