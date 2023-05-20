#include "include/dijkstra.h"
// TODO : supposed to work now
void dijkstra(void) { return; }

    if(distance_cord(x_start,y_start,x_end,y_end) > autonomie){
        //label_list *ll = create_label_list();
        //ll = *add_label(ll, b, INFINITY);
        bornes_graph graph_csv = generate_graph_fromCSV(autonomie);
        /*
        int prev_label_index = -1; 
        //à ajouter dans la structure pour garder en mémoire le chemin du diskstra
        
        while(graph_csv -> size != 0){
            int min_label = INFINITY;
            int min_index = -1;
            for(int i = 0, i < size, i++){
                int label = distance(b0, borne(graph_csv -> bornes_graph, i));
                //fonction à définir
                
                if (label > autonomie){label = INFINITY;}
                if(label < min_label){
                    min_label = label;
                    index = i;
                }
                
                label_add(label, graph_csv -> bornes_graph, i,prev_label_index);
                //label_add garde le minimum des labels
            }
            b0 = borne(graph_csv -> bornes_graph, index);
            prev_label_index = index;
            graph_csv = remove_borne(graph_csv -> bornes_graph, index);
            chemin_bornes = add_borne(b0);
        }
        //Todo remontée et récupération du chemin
        */
    }

    else{
        // le chemin entre les deux points est possible 
        //sans passer par deux bornes
        chemin_bornes = add_borne(b1);
    }
    
    return chemin_bornes; 
}
/*
label_list *create_label_list(void){
    label_list *ll = malloc(sizeof(label_list));
    ll -> label = 0;
    ll -> index = 0;
    ll -> prev_label_index = -1;
    ll -> next = NULL;
    return label_list; 
}

void destroy_label_list(label_list *ll){
    //TODO
}

label_list *add_label(label_list* ll, borne* b, int label){
    if(ll -> index == 0){
        ll -> borne = b;
        ll -> label = label;
        ll -> next = ll;
        ll -> index = 1;
    }
    else{
        label_list *new_ll = mallox(sizeof(label_list));
        new_ll -> index = ll -> index + 1
        new_ll -> label = label;
        new_ll -> next = ll;
         
    }
}

*/

//il vaudrait peut être mieux ajouter label dans la structure 
//borne_list directement
int distance_cord(double x_start, double y_start, 
                double x_end, double y_end){
    return sqrt((x_end-x_start)**2 +(y_end - y_start)**2);
}

int main(void) { return 0; }
