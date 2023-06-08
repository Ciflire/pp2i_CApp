#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 64

#ifndef LINE_H

#define LINE_H
// Structures creations
struct line {
  int size;
  char **info;
};

typedef struct line line;

// Init the structure for a given size (here 3 for cars, 4 for borne)
// Remember t define the MAX_STR_LEN in the header (default 256)
line *line_create(int size);

// Destroy the structure
void line_destroy(line *l);

// Get the size of the structure
int line_getSize(line *l);

// Print the structure
void line_print(line *l);
#endif


