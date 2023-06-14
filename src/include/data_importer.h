#include "borne_list.h"
#include "car_list.h"
#include "line.h"
#include "line_array.h"

#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

void borne_list_dataImporter(line_array *file, borne_list *list_borne);
void car_list_dataImporter(line_array *file, car_list *list_car);

#endif
