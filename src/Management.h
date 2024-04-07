#ifndef PROJECT1_MANAGEMENT_H
#define PROJECT1_MANAGEMENT_H
#include "Graph.h"
#include <queue>

/**
 * @brief Auxiliary struct containing old and new flow
 */
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

    // Auxiliary functions to max flow algorithm
    void testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual);
    bool findAugmentingPath( ServicePoint *s, ServicePoint *t, bool balanced=false);
    double findMinResidualAlongPath(ServicePoint *s, ServicePoint *t);
    void edmondsKarp( ServicePoint* s, ServicePoint* t, bool balanced=false);
    void augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f);

    std::unordered_map<std::string,int> getMaxFlow(bool balanced = false);
    std::pair<std::string,int> getMaxFlowCity(ServicePoint * citySink);
    std::unordered_map<std::string,int> getFlowDeficit ();
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByReservoirFail(ServicePoint * reservoir);
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByStationFail(ServicePoint* downStation);
    std::vector<std::pair<std::string, flowDiff>> getCitiesAffectedByPipeRupture(Pipe* e);
    std::vector<std::pair<Pipe *,flowDiff>> getCrucialPipesToCity(ServicePoint* sp);

    // Metrics
    float getAveragePipePressure();
    float getVariancePipePressure();

    bool findAugmentingPathBalance( ServicePoint *s, ServicePoint *t);
    double findMinResidualAlongPathBalance(ServicePoint *s, ServicePoint *t);
    void edmondsKarpBalance( ServicePoint* s, ServicePoint* t, bool reset=true);
    void augmentFlowAlongPathBalance(ServicePoint *s, ServicePoint *t, double f);
    std::unordered_map<std::string,int> getMaxFlowBalance();
    void closeToAvg(ServicePoint *superSource, ServicePoint *superSink);
};

#endif //PROJECT1_MANAGEMENT_H
