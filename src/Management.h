
#ifndef PROJECT1_MANAGEMENT_H
#define PROJECT1_MANAGEMENT_H
#include "Graph.h"

class Management {
public:
    void getMaxFlow(); //guarda no vetor, chamar N vezes getMaxFlowCity para N cidades
    int getMaxFlowCity(); //retorna e guarda do vetor (check se ja esta populado para essa cidade)
};


#endif //PROJECT1_MANAGEMENT_H
