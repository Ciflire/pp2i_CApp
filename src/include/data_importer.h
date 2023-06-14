#include "borne_list.h"
#include "car_list.h"
#include "line.h"
#include "line_array.h"

#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

void borne_list_dataImporter(csv_import *file, borne_list *list_borne);
void car_list_dataImporter(csv_import *file, car_list *list_car);

#endif
