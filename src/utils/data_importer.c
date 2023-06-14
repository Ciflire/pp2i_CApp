#include "../include/data_importer.h"

// import the data from a line_arrayer struct to a borne_list struct
void borne_list_dataImporter(line_array *file, borne_list *list_borne) {
  int number_of_line = line_array_getSize(file);
  int id = 1;
  for (int i = 0; i < number_of_line; i++) {
    line *current_line = file->line[i]; // get the current line number i

    // create a new borne with data stored in line_array(changing its type) and
    // append it to the borne_list
    borne_list_append(list_borne, borne_create(id, atoi(current_line->info[2]),
                                               atoi(current_line->info[3]),
                                               atof(current_line->info[1]),
                                               atof(current_line->info[0])));
    if(id==89){
      printf("id: %d\n", id);
      borne_print(borne_list_getBorneById(list_borne, 89));
    }
    id++;
  }
}

// import the data from a line_arrayer struct to a car_list struct
void car_list_dataImporter(line_array *file, car_list *list_car) {
  int number_of_line = line_array_getSize(file);
  int id = 1;
  for (int i = 0; i < number_of_line; i++) {
    line *current_line = file->line[i]; // get the current line number i

    // create a new car with data stored in line_array(changing its type) and
    // append it to the car_list
    car_list_append(list_car, car_create(current_line->info[0], id,
                                         atoi(current_line->info[1]),
                                         atof(current_line->info[2])));
    id++;
  }
}
