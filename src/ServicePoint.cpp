#include "ServicePoint.h"

ServicePoint::ServicePoint() {}

void ServicePoint::addPipe(Pipe * pipe) {
    adj.push_back(pipe);
}

void ServicePoint::addIncomingPipe(Pipe * pipe) {
    incoming.push_back(pipe);
}

void ServicePoint::removeIncomingPipe(Pipe * pipe) {
    auto it = incoming.begin();
    while (it != incoming.end()) {
        if ((*it) == pipe) {
            incoming.erase(it);
            break;
        } else {
            it++;
        }
    }
}

void ServicePoint::removeOutgoingPipe(Pipe * pipe) {
    auto it = adj.begin();
    while (it != adj.end()) {
        if ((*it) == pipe) {
            adj.erase(it);
            break;
        } else {
            it++;
        }
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

Pipe * ServicePoint::getPath() const {
    return this->path;
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

void ServicePoint::setPath(Pipe *path) {
    this->path=path;
}

void ServicePoint::setPred(Pipe * pred) {
    this->path = pred;
}

void ServicePoint::setOperational(bool b) {
    operational=b;
}

bool ServicePoint::isOperational() const {
    return operational;
}
