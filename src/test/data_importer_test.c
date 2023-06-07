#include "../include/data_importer.h"
#include "../include/csvParser.h"
#include "../include/timer.h"

int main(void){
    timer_start();
    char *file_path = "data/bornes.csv";
    csv_import *file = csv_import_create(MAX_LINES, 4);
    csvParser(file_path, 1, file);
    timer_stop();
    printf("Time to parse the file: ");
    timer_print();
    borne_list *list_borne = borne_list_create();
    borne_data_importer(file, list_borne);
    timer_stop();
    printf("Time to import the data: ");
    timer_print();
    csv_import_destroy(file);
    borne_list_print(list_borne);
    borne_list_destroy(list_borne);
    timer_stop();
    printf("Time to destroy the data: ");
    timer_print();
    return 0;
}
