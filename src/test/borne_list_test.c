#include "../include/borne_list.h"

int main(){
    borne_list *list = borne_list_create();
    borne *b1 = borne_create(1, 2, 25, 3.0, 4.0);
    borne *b2 = borne_create(2, 2, 25, 3.0, 4.0);
    borne *b3 = borne_create(3, 2, 55, 5.0, 1.2);


    borne_list_print(list);
    borne_list_append(list, b1);
    borne_list_append(list, b2);
    borne_list_append(list, b3);
    borne_list_print(list);

    borne_list_destroy(list);
    return 0;
}
