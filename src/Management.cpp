#include <stdexcept>
#include "Management.h"

Management::Management(Graph *graph) {
    this->g=graph;
}

void Management::testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual) {
    // Check if the ServicePoint 'w' is not visited and there is residual capacity
    if(!w->isVisited() && residual>0 && w->isOperational() && e->isOperational()){
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
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

// Function to find the minimum residual capacity along the augmenting path
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

// Function to augment flow along the augmenting path with the given flow value
void Management::augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
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

// Main function implementing the Edmonds-Karp algorithm
void Management::edmondsKarp( ServicePoint* s, ServicePoint* t) {

    // Validate source and target vertices
    if(s==nullptr || t== nullptr || s==t){
        throw std::logic_error("Invalid source and/or target ServicePoint");
    }

    // Initialize flow on all Pipes to 0
    for(ServicePoint* v:g->getServicePointSet()){
        v->setPath(nullptr);
        v->setPred(nullptr);
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

std::vector<std::pair<Pipe *,flowDiff>> Management::getCrucialPipesToCity(ServicePoint* sp){
    if(maxFlowCity.empty())
        getMaxFlow();
    std::vector<std::pair<Pipe *,flowDiff>> crucialPipes;
    for (auto e:g->getPipeSet()){
        e->setOperational(false);
        if(e->getReverse()!=nullptr)
            e->getReverse()->setOperational(false);
        std::unordered_map<std::string,int> newValues=getMaxFlow();
        if (maxFlowCity[sp->getCode()]>newValues[sp->getCode()]){
            flowDiff diff = {maxFlowCity[sp->getCode()],newValues[sp->getCode()]};
            crucialPipes.push_back(std::make_pair(e,diff));
        }
        e->setOperational(true);
        if(e->getReverse()!=nullptr)
            e->getReverse()->setOperational(true);
    }
    return crucialPipes;
}

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

