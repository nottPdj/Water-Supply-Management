#include <stdexcept>
#include "Management.h"
/**
 * @brief Management Constructor
 * @param graph
 */
Management::Management(Graph *graph) {
    this->g=graph;
}

/**
 * @brief Checks if the Service Point is not visited and there is residual capacity, then marks as visited, sets path, and enqueue it
 * @param q - queue of ServicePoints
 * @param e - Pipe
 * @param w - ServicePoint
 * @param residual
 * @details Time Complexity O(1)
 */
void Management::testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual) {
    if(!w->isVisited() && residual>0 && w->isOperational() && e->isOperational()){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * @brief Finds an augmenting path using Breadth-First Search
 * @param s - source ServicePoint
 * @param t - target ServicePoint
 * @return True if path is found
 * @details Time Complexity O(V+E) V = number of ServicePoints, E = number of Pipes
 */
bool Management::findAugmentingPath( ServicePoint *s, ServicePoint *t) {
    // Mark all vertices as not visited
    for(ServicePoint*v:g->getServicePointSet()){
        v->setVisited(false);
    }

    // Mark the source ServicePoint as visited and enqueue it
    s->setVisited(true);
    std::queue<ServicePoint*> q;
    q.push(s);

    // BFS to find an augmenting path
    while(!q.empty() && !t->isVisited()){
        auto v=q.front();
        q.pop();
        if(!v->isOperational())
            continue;
        // Process outgoing Pipes
        for(Pipe* e : v->getAdj()){
            testAndVisit(q,e,e->getDest(),e->getCapacity()- e->getFlow());
        }
        // Process incoming Pipes
        for(Pipe* e : v->getIncoming()){
            testAndVisit(q,e,e->getOrig(),e->getFlow());
        }
    }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

/**
 * @brief Find the minimum residual capacity along the augmenting path
 * @param s - source ServicePoint
 * @param t - target ServicePoint
 * @return f
 * @details Time Complexity O(E) E = number of Pipes between s and t
 */
double Management::findMinResidualAlongPath(ServicePoint *s, ServicePoint *t) {
    double f = INF;
    // Traverse the augmenting path to find the minimum residual capacity
    ServicePoint *v=t;
    while(v!=s){
        auto e=v->getPath();
        if(e->getDest()==v){
            f=std::min(f,e->getCapacity()-e->getFlow());
            v=e->getOrig();
        }
        else{
            f=std::min(f,e->getFlow());
            v=e->getDest();
        }
    }
    // Return the minimum residual capacity
    return f;
}

/**
 * @brief Augments the flow along the augmenting path with the given flow value
 * @param s - source ServicePoint
 * @param t - target ServicePoint
 * @param f - flow value
 * @details Time Complexity O(E) E = number of Pipes between s and t
 */
void Management::augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f) {
    ServicePoint *v=t;
    while(v!=s){
        auto e=v->getPath();
        double flow=e->getFlow();
        if(e->getDest()==v){
            e->setFlow(flow+f);
            v=e->getOrig();
        }
        else{
            e->setFlow(flow-f);
            v=e->getDest();
        }
    }
}

/**
 * @brief Performs the EdmondsKarp
 * @param s - source ServicePoint
 * @param t - target ServicePoint
 * @details Time Complexity O(V*E²)
 */
void Management::edmondsKarp( ServicePoint* s, ServicePoint* t) {

    // Validate source and target vertices
    if(s==nullptr || t== nullptr || s==t){
        throw std::logic_error("Invalid source and/or target ServicePoint");
    }

    // Initialize flow on all Pipes to 0
    for(ServicePoint* v:g->getServicePointSet()){
        v->setPath(nullptr);
        for(Pipe* e : v->getAdj()){
            e->setFlow(0);
        }
    }

    // While there is an augmenting path, augment the flow along the path
    while(findAugmentingPath(s,t)){
        double f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
    }
}

/**
 * @brief Gets the max flow overall.
 * @return flowPerCity
 */
std::unordered_map<std::string,int> Management::getMaxFlow() { //each city do for super sink, for each city do for ServicePoint(city)
    Reservoir *superSource = new Reservoir("supersource", "x","0", "SRC", INF);
    g->addReservoir(superSource);
    for(ServicePoint* v:g->getReservoirSet()){
        if (v->getCode() != "SRC") {
            g->addPipe("SRC", v->getCode(), ((Reservoir*)v)->getMaxDelivery());
        }
    }
    City *superSink = new City("supersink","01","SINK",INF,INF);
    g->addCity(superSink);
    for(ServicePoint* v:g->getCitiesSet()){
        if (v->getCode() != "SINK") {
            g->addPipe(v->getCode(), "SINK", ((City*)v)->getDemand());
        }
    }

    edmondsKarp(superSource,superSink);

    std::unordered_map<std::string,int> flowPerCity;
    g->removeServicePoint(superSource);
    g->removeServicePoint(superSink);
    for(ServicePoint* v: g->getCitiesSet()){
        int maxflow=0;
        for(Pipe* e: v->getIncoming()){
            maxflow+=e->getFlow();
        }
        flowPerCity.insert(std::make_pair(v->getCode(),maxflow));
    }
    if(maxFlowCity.empty())
        maxFlowCity = flowPerCity;
    return flowPerCity;
}

/**
 * @brief Gets the max flow of a specific City
 * @param citySink
 * @return deficitVector
 */
std::pair<std::string,int> Management::getMaxFlowCity(ServicePoint * citySink) {
    int maxflow = 0;
    Reservoir *superSource = new Reservoir("supersource", "x","0", "SRC", INF);
    g->addReservoir(superSource);
    for(ServicePoint* v : g->getReservoirSet()){
        if (v->getCode() != "SRC") {
            g->addPipe("SRC", v->getCode(), ((Reservoir*)v)->getMaxDelivery());
        }
    }
    edmondsKarp(superSource,citySink);
    for (Pipe *p : citySink->getIncoming()){
        maxflow += p->getFlow();
    }
    maxflow=std::min(maxflow,((City*)citySink)->getDemand());
    g->removeServicePoint(superSource);
    return std::make_pair(citySink->getCode(),maxflow);
}

std::unordered_map<std::string,int> Management::getFlowDeficit() {
    std::unordered_map<std::string,int> deficitVector;
    if(maxFlowCity.empty()){
        maxFlowCity=getMaxFlow();
    }
    for(auto v: maxFlowCity){
        City* c =(City*)g->findServicePoint(v.first);
        if(c->getDemand()>v.second)
            deficitVector.insert(std::make_pair(v.first,c->getDemand()-v.second));
    }
    return deficitVector;
}


/**
 * @brief Gets the cities affected by a reservoir fail.
 * @param reservoir
 * @return affectedCities
 */
std::vector<std::pair<std::string, flowDiff>> Management::getCitiesAffectedByReservoirFail(ServicePoint * reservoir) {
    std::vector<std::pair<std::string, flowDiff>> affectedCities;

    if (maxFlowCity.empty()) {
        getMaxFlow();
    }

    reservoir->setOperational(false);
    std::unordered_map<std::string,int> newFlow = getMaxFlow();

    for (auto it = newFlow.begin(); it != newFlow.end(); ++it) {
        std::string city = it->first;
        int oldFlow = maxFlowCity[city];
        int newFlow = it->second;
        if (newFlow < oldFlow) {
            flowDiff diff = {oldFlow, newFlow};
            affectedCities.push_back(std::make_pair(city, diff));
        }
    }
    reservoir->setOperational(true);
    return affectedCities;
}


/**
 * @brief Gets the cities affected by a Pipe rupture.
 * @param e
 * @return citiesAffected
 */
std::vector<std::pair<std::string, flowDiff>> Management::getCitiesAffectedByPipeRupture(Pipe* e){
    if(maxFlowCity.empty())
        getMaxFlow();
    std::vector<std::pair<std::string, flowDiff>> citiesAffected;
    e->setOperational(false);
    if(e->getReverse()!=nullptr)
        e->getReverse()->setOperational(false);
    std::unordered_map<std::string,int> newValues=getMaxFlow();
    for(auto v: g->getCitiesSet()){
        if(maxFlowCity[v->getCode()]>newValues[v->getCode()]){
            flowDiff fd = {maxFlowCity[v->getCode()],newValues[v->getCode()]};
            citiesAffected.push_back(std::make_pair(v->getCode(),fd));
        }
    }
    e->setOperational(true);
    if(e->getReverse()!=nullptr)
        e->getReverse()->setOperational(true);
    return citiesAffected;
}

/**
 * @brief Gets the Crucial Pipes to a City. Checks if the flow of a City decreases from a Pipe removal.
 * @param sp
 * @return crucialPipes
 */
std::vector<std::pair<Pipe *,flowDiff>> Management::getCrucialPipesToCity(ServicePoint* sp){
    if(maxFlowCity.empty())
        getMaxFlow();
    std::vector<std::pair<Pipe *,flowDiff>> crucialPipes;
    for (auto e: g->getPipeSet()) {
        e->setVisited(false);
    }
    for (auto e:g->getPipeSet()){
        if (e->isVisited())
            continue;
        e->setOperational(false);
        if(e->getReverse()!=nullptr)
            e->getReverse()->setOperational(false);
        std::unordered_map<std::string,int> newValues=getMaxFlow();
        if (maxFlowCity[sp->getCode()]>newValues[sp->getCode()]){
            flowDiff diff = {maxFlowCity[sp->getCode()],newValues[sp->getCode()]};
            crucialPipes.push_back(std::make_pair(e,diff));
        }
        e->setOperational(true);
        if(e->getReverse()!=nullptr) {
            e->getReverse()->setOperational(true);
            e->getReverse()->setVisited(true);
        }
    }
    return crucialPipes;
}

/**
 * @brief Gets the cities affected by a Station failing
 * @param downStation
 * @return affectedCities
 */
std::vector<std::pair<std::string, flowDiff>> Management::getCitiesAffectedByStationFail(ServicePoint* downStation) {
    std::vector<std::pair<std::string, flowDiff>> affectedCities;
    if (maxFlowCity.empty()){
        getMaxFlow();
    }

    downStation->setOperational(false);
    std::unordered_map<std::string,int> newFlowCity = getMaxFlow();
    downStation->setOperational(true);

    for (ServicePoint* c : g->getCitiesSet()){
        int diff = newFlowCity[c->getCode()] - maxFlowCity[c->getCode()];
        if (diff < 0){
            flowDiff fd = {maxFlowCity[c->getCode()], newFlowCity[c->getCode()]};
            affectedCities.push_back(std::make_pair(c->getCode(), fd));
        }
    }
    return affectedCities;
}

