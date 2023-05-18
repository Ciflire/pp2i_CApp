
typedef struct {
    double X;
    double Y;
    double puissance;
    int nombre;
} borne_t;

int csv_bornes (borne_t bornes[]);
int csv_adjacence (float * longeurs);
int index_of_distance(int a, int b);
void generateListFromCSV(char* csvLine, int* resultList, int* resultSize);
