#include "../include/csv_import.h"

int csv_import_getSize(csv_import *file) { return file->size; }

int line_getSize(line *l) { return l->size; }