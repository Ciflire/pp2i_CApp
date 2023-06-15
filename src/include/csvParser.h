#include "line_array.h"

#ifndef CSV_PERSER_H
#define CSV_PERSER_H

// Use this function with a csv import with the right number of column
// and the right number of lines to skip
void csvParser(char *path, int linesToSkip, line_array *file);

#endif
