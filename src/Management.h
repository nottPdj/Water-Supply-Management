#ifndef PROJECT1_MANAGEMENT_H
#define PROJECT1_MANAGEMENT_H
#include "Graph.h"
#include <queue>


class Management {
private:
    Graph* g;
    std::vector<std::pair<std::string,int>> maxFlowCity;
public:
    Management(Graph * graph);
    void testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual);
    bool findAugmentingPath( ServicePoint *s, ServicePoint *t);
    double findMinResidualAlongPath(ServicePoint *s, ServicePoint *t);
    void edmondsKarp( ServicePoint* s, ServicePoint* t);
    void augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f);
    std::vector<std::pair<std::string,int>> getMaxFlow(); //guarda no vetor, chamar N vezes getMaxFlowCity para N cidades
    std::pair<std::string,int> getMaxFlowCity(ServicePoint * citySink); //retorna e guarda do vetor (check se ja esta populado para essa cidade)
    std::vector<std::pair<std::string,int>> getFlowDeficit ();
};


#endif //PROJECT1_MANAGEMENT_H
