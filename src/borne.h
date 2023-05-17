#ifndef BORNE_H
#define BORNE_H

typedef struct borne{
    int id;
    double xpos;
    double ypos;
    double power;
    int qte;
};

typedef struct borne borne;

borne* create_borne(int id, double xpos, double ypos, double power, int qte);


#endif