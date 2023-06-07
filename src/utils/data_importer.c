#include "../include/data_importer.h"


//import the data from a csv_importer struct to a borne_list struct
void borne_data_importer(csv_import *file, borne_list *list_borne) {
  int number_of_line = csv_import_getSize(file);
  int id = 0;
  for (int i = 0; i < number_of_line; i++) {
    line *current_line = file->line[i]; // get the current line number i

    //create a new borne with data stored in csv_import(changing its type) and append it to the borne_list
    borne_list_append(list_borne, borne_create(id, atoi(current_line->info[2]),
                                               atoi(current_line->info[3]),
                                               atof(current_line->info[0]),
                                               atof(current_line->info[1])));
    id++;
  }
}


//import the data from a csv_importer struct to a car_list struct
void car_data_importer(csv_import *file, car_list *list_car) {
  int number_of_line = csv_import_getSize(file);
  int id = 0;
  for (int i = 0; i < number_of_line; i++) {
    line *current_line = file->line[i]; // get the current line number i

    //create a new car with data stored in csv_import(changing its type) and append it to the car_list
    car_list_append(list_car, car_create(current_line->info[0], id,
                                         atoi(current_line->info[1]),
                                         atof(current_line->info[2])));
    id++;
  }
}
