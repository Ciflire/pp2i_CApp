#include "../include/data_importer.h"
#include <string.h>

// Import the data from a line_array struct to a borne_list struct
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
    id++;
  }
}

// Import the data from a line_array struct to a car_list struct
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

void borne_list_memoryImporter(line_array *pdcList, borne_list *list_borne) {
  printf("In importer\n");
  borne_list *bl = list_borne;
  char *arr = calloc(256,sizeof(char));
  char *dep = calloc(256,sizeof(char));
  for (int i = 0; i < line_array_getSize(pdcList); i++) {
    line *current_line = pdcList->line[i];
    for (int j = 0; j < bl->borne->pdc - 1; j++) {
      char *pdc = current_line->info[j];/* 
      printf("pdc size : %lu\n", strlen(pdc));
      printf("pdc : %s\n", pdc); */
      int k = 0;
      int l = 0;
      bool in_parenthesis = false;
      bool before_comma = true;

      while (pdc[k] != '\0') {
        if (pdc[k] == '[') {
          k++;
        } else if (pdc[k] == '(') {
          in_parenthesis = true;
          before_comma = true;
        } else if (pdc[k] == ')') {
          in_parenthesis = false;
          dep[l] = '\0';
          printf("arr : %s\n", arr);
          printf("dep : %s\n", dep);
          horaire_list_insert(bl->borne->horairePdc[j],
                              horaire_createWithValues(atoi(arr), atoi(dep)));
          l = 0;
        } else if (pdc[k] == ',' && in_parenthesis) {
          arr[l] = '\0';
          l = 0;
          before_comma = false;
        } else if (pdc[k] == ',' && !in_parenthesis) {
          l = 0;
          before_comma = true;
        }
        else if (pdc[k] == ']') {
          k++;
        } else {
          if (before_comma) {
            arr[l] = pdc[k];
            printf("arr : %s\n", arr);
          } else {
            dep[l] = pdc[k];
          }
          l++;
        }
        k++;
      }
    }
  }
}
