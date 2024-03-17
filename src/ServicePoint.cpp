//
// Created by pedro on 17-03-2024.
//

#include "ServicePoint.h"

ServicePoint<T>::ServicePoint(T in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a ServicePoint (this),
 * with a given destination ServicePoint (d) and edge weight (w).
 */
Edge<T> * ServicePoint<T>::addEdge(ServicePoint<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a ServicePoint (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool ServicePoint<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        ServicePoint<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a ServicePoint.
 */
void ServicePoint<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool ServicePoint<T>::operator<(ServicePoint<T> & ServicePoint) const {
    return this->dist < ServicePoint.dist;
}

T ServicePoint<T>::getInfo() const {
    return this->info;
}

std::vector<Edge<T>*> ServicePoint<T>::getAdj() const {
    return this->adj;
}

bool ServicePoint<T>::isVisited() const {
    return this->visited;
}

bool ServicePoint<T>::isProcessing() const {
    return this->processing;
}

unsigned int ServicePoint<T>::getIndegree() const {
    return this->indegree;
}

double ServicePoint<T>::getDist() const {
    return this->dist;
}

Edge<T> *ServicePoint<T>::getPath() const {
    return this->path;
}

std::vector<Edge<T> *> ServicePoint<T>::getIncoming() const {
    return this->incoming;
}

void ServicePoint<T>::setInfo(T in) {
    this->info = in;
}

void ServicePoint<T>::setVisited(bool visited) {
    this->visited = visited;
}

void ServicePoint<T>::setProcesssing(bool processing) {
    this->processing = processing;
}

void ServicePoint<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void ServicePoint<T>::setDist(double dist) {
    this->dist = dist;
}

void ServicePoint<T>::setPath(Edge<T> *path) {
    this->path = path;
}

void ServicePoint<T>::deleteEdge(Edge<T> *edge) {
    ServicePoint<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}