#ifndef PROJECT1_MANAGEMENT_H
#define PROJECT1_MANAGEMENT_H
#include "Graph.h"
#include <queue>

struct flowDiff{
    int oldFlow;
    int newFlow;
};


class Management {
private:
    Graph* g;
    std::unordered_map<std::string,int> maxFlowCity;
public:
    Management(Graph * graph);
    void testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual);
    bool findAugmentingPath( ServicePoint *s, ServicePoint *t);
    double findMinResidualAlongPath(ServicePoint *s, ServicePoint *t);
    void edmondsKarp( ServicePoint* s, ServicePoint* t);
    void augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f);
    std::unordered_map<std::string,int> getMaxFlow(); //guarda no vetor, chamar N vezes getMaxFlowCmity para N cidades
    std::pair<std::string,int> getMaxFlowCity(ServicePoint * citySink); //retorna e guarda do vetor (check se ja esta populado para essa cidade)
    std::unordered_map<std::string,int> getFlowDeficit ();
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByReservoirFail(ServicePoint * reservoir);
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByStationFail(ServicePoint* downStation);
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByPipeRupture(Pipe* e);
    std::vector<std::pair<Pipe *,flowDiff>> getCrucialPipesToCity(ServicePoint* sp);
};


#endif //PROJECT1_MANAGEMENT_H
