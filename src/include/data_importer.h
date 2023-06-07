#include "borne_list.h"
#include "car_list.h"
#include "csv_import.h"
#include "line.h"

#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

void borne_data_importer(csv_import *file, borne_list *list_borne);
void car_data_importer(csv_import *file, car_list *list_car);

#endif