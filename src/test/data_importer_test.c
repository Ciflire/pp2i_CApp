#include "../include/data_importer.h"
#include "../include/csvParser.h"
#include "../include/timer.h"

int main(void){
    //test the import of bornes.csv and vehicules.csv
    timer_start();
    char *file_path = "data/borne_cleaned.csv";
    line_array *file = line_array_create(MAX_LINES_BORNES, 4);
    csvParser(file_path,  1, file);

    printf("    [Debug data_importer] : Test csvParser passed\n");
    timer_stop();
    printf("Time to parse the bornes file : ");
    timer_print();
    borne_list *list_borne = borne_list_create();
    //import the data to a bornes_list
    borne_list_dataImporter(file, list_borne);

    printf("    [Debug data_importer] : Test borne_list_dataImporter passed\n");
    timer_stop();
    printf("Time to import the bornes data: ");
    timer_print();
    line_array_destroy(file);
    borne_list_destroy(list_borne);
    timer_stop();
    printf("Time to destroy the bornes data: ");
    timer_print();

    timer_reset();

    timer_start();
    char *file_path2 = "data/Vehicules.csv";
    // import the data i,n car.csv
    line_array *file2 = line_array_create(MAX_LINES_CARS, 3);
    csvParser(file_path2, 0, file2);
    printf("    [Debug data_importer] : Test csvParser passed\n");

    timer_stop();
    printf("Time to parse the car file : ");
    timer_print();
    car_list *list_car = car_list_create();
    // import the data to a car_list
    car_list_dataImporter(file, list_car);
    printf("    [Debug data_importer] : Test car_list_dataImporter passed\n");

    timer_stop();
    printf("Time to import the car data: ");
    timer_print();
    line_array_destroy(file);
    car_list_destroy(list_car);
    timer_stop();
    printf("Time to destroy the car data: ");
    timer_print();
    return 0;
}
