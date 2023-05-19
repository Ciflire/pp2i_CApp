#include "csv_handler.h"
#include "bornes_graph.h"

int main(void){
    printf("Hello world\n");
    bornes_graph *bg = generate_graph_fromCSV(150);
    if (bg == NULL) {
        printf("Error while generating graph\n");
        return 1;
    }
    printf("Graph generated\n");
    destroy_bornes_graph(bg);
    printf("Graph destroyed\n");
    return 0;
}
