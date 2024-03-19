#include "ServicePoint.h"

ServicePoint::ServicePoint() {}

void ServicePoint::addPipe(Pipe * pipe) {
    adj.push_back(pipe);
}

void ServicePoint::removePipe(Pipe * pipe) {
    // Remove the pipe from the adjacency list
    auto it = adj.begin();
    while (it != adj.end()) {
        if ((*it) == pipe) {
            it = adj.erase(it);
            break;
        } else {
            it++;
        }
    }
    // Remove the pipe from the incoming pipe list
    pipe->getDest()->removeIncomingPipe(pipe);
    delete pipe;
}

void ServicePoint::removeIncomingPipe(Pipe * pipe) {
    auto it = incoming.begin();
    while (it != incoming.end()) {
        if ((*it) == pipe) {
            it = incoming.erase(it);
            break;
        } else {
            it++;
        }
    }
}

void ServicePoint::removeOutgoingPipes() {
    auto it1 = adj.begin();
    while (it1 != adj.end()) {
        Pipe *pipe = *it1;
        removeIncomingPipe(pipe);
        it1++;
    }
    // Remove all pipes from the adjacency list
    auto it2 = adj.begin();
    while (it2 != adj.end()) {
        Pipe * pipe = *it2;
        it2 = adj.erase(pipe);
        delete pipe;
    }
}


std::vector<Pipe *> ServicePoint::getAdj() const {
    return this->adj;
}

bool ServicePoint::isVisited() const {
    return this->visited;
}

bool ServicePoint::isProcessing() const {
    return this->processing;
}

unsigned int ServicePoint::getIndegree() const {
    return this->indegree;
}

double ServicePoint::getDist() const {
    return this->dist;
}

Pipe * ServicePoint::getPred() const {
    return this->pred;
}

std::vector<Pipe *> ServicePoint::getIncoming() const {
    return this->incoming;
}


void ServicePoint::setVisited(bool visited) {
    this->visited = visited;
}

void ServicePoint::setProcesssing(bool processing) {
    this->processing = processing;
}

void ServicePoint::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void ServicePoint::setDist(double dist) {
    this->dist = dist;
}

void ServicePoint::setPred(Pipe * pred) {
    this->path = pred;
}