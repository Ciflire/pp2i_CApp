#include "../include/borne_list.h"
#include <time.h>
#include "../include/timer.h"


int main(){

    for (int i = 1; i < 5; i++){
        timer_start();
        borne_list *list = borne_list_create();
        for(int j = 0; j < (1000000 * i); j++){
            borne* b = borne_create(j, 1, 25, 1.0, 1.0);
            borne_list_append(list, b);
        }
        timer_stop();
        timer_print();
        borne_list_destroy(list);
    }
    return 0;
}
