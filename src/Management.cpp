#include <stdexcept>
#include "Management.h"

void testAndVisit(std::queue<ServicePoint*> &q, Pipe*e, ServicePoint *w, double residual) {
    // Check if the ServicePoint 'w' is not visited and there is residual capacity
    if(!w->isVisited() && residual>0){
    // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
bool findAugmentingPath(Graph *g, ServicePoint *s, ServicePoint *t) {
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
double findMinResidualAlongPath(ServicePoint *s, ServicePoint *t) {
    double f = std::INF;
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
void augmentFlowAlongPath(ServicePoint *s, ServicePoint *t, double f) {
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
void edmondsKarp(Graph *g, int source, int target) {
    // Find source and target vertices in the graph
    ServicePoint* s = g->findServicePoint(source);
    ServicePoint* t = g->findServicePoint(target);

    // Validate source and target vertices
    if(s==nullptr || t== nullptr || s==t){
        throw std::logic_error("Invalid source and/or target ServicePoint");
    }

    // Initialize flow on all Pipes to 0
    for(ServicePoint* v:g->getServicePointSet()){
        for(Pipe* e : v->getAdj()){
            e->setFlow(0);
        }
    }

    // While there is an augmenting path, augment the flow along the path
    while(findAugmentingPath(g,s,t)){
        double f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
    }
}


void Management::getMaxFlow() {
}

int Management::getMaxFlowCity(std::string cityName) {
    return 0;
}
