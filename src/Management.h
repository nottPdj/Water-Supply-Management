#ifndef PROJECT1_MANAGEMENT_H
#define PROJECT1_MANAGEMENT_H
#include "Graph.h"
#include <queue>


class Management {
private:
    Graph* g;
public:
    Management(Graph * graph);
    void testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual);
    bool findAugmentingPath(Graph *g, ServicePoint *s, ServicePoint *t);
    double findMinResidualAlongPath(ServicePoint *s, ServicePoint *t);
    void edmondsKarp(Graph *g, ServicePoint* s, ServicePoint* t);
    void augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f);
    std::vector<std::pair<std::string,int>> getMaxFlow(); //guarda no vetor, chamar N vezes getMaxFlowCity para N cidades
    int getMaxFlowCity(std::string city); //retorna e guarda do vetor (check se ja esta populado para essa cidade)
};


#endif //PROJECT1_MANAGEMENT_H
