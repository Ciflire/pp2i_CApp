#include "../include/car_list.h"
#include <time.h>
#include "../include/timer.h"


int main(){

    for (int i = 1; i < 5; i++){
        timer_start();
        car_list *list = car_list_create();
        for(int j = 0; j < (1000000 * i); j++){
            car* b = car_create("Balek", j, 1.0, 1.0);
            car_list_append(list, b);
        }
        timer_stop();
        timer_print();
        car_list_destroy(list);
    }
    return 0;
}
