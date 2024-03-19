//
// Created by pedro on 17-03-2024.
//

#include "Graph.h"

int Graph::getNumServicePoint() const {
    return ServicePointSet.size();
}

std::vector<ServicePoint *> Graph::getServicePointSet() const {
    return ServicePointSet;
}

/*
 * Auxiliary function to find a ServicePoint with a given content.
 */
ServicePoint* Graph::findServicePoint(const std::string &code) {
    return servicePointByCode[code];
}

/*
 * Finds the index of the ServicePoint with a given content.
 */
int Graph::findServicePointIdx(const  &in) const {
    for (unsigned i = 0; i < ServicePointSet.size(); i++)
        if (ServicePointSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a ServicePoint with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a ServicePoint with that content already exists.
 */
bool Graph::addServicePoint(const T &in) {
    if (findServicePoint(in) != nullptr)
        return false;
    ServicePointSet.push_back(new ServicePoint<T>(in));
    return true;
}

/*
 *  Removes a ServicePoint with a given content (in) from a graph (this), and
 *  all outgoing and incoming Pipes.
 *  Returns true if successful, and false if such ServicePoint does not exist.
 */
bool Graph::removeServicePoint(const T &in) {
    for (auto it = ServicePointSet.begin(); it != ServicePointSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingPipes();
            for (auto u : ServicePointSet) {
                u->removePipe(v->getInfo());
            }
            ServicePointSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an Pipe to a graph (this), given the contents of the source and
 * destination vertices and the Pipe weight (w).
 * Returns true if successful, and false if the source or destination ServicePoint does not exist.
 */
template <class T>
bool Graph::addPipe(const T &sourc, const T &dest, double w) {
    auto v1 = findServicePoint(sourc);
    auto v2 = findServicePoint(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addPipe(v2, w);
    return true;
}

/*
 * Removes an Pipe from a graph (this).
 * The Pipe is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such Pipe does not exist.
 */
bool Graph::removePipe(const T &sourc, const T &dest) {
    ServicePoint<T> * srcServicePoint = findServicePoint(sourc);
    if (srcServicePoint == nullptr) {
        return false;
    }
    return srcServicePoint->removePipe(dest);
}

bool Graph::addBidirectionalPipe(const T &sourc, const T &dest, double w) {
    auto v1 = findServicePoint(sourc);
    auto v2 = findServicePoint(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addPipe(v2, w);
    auto e2 = v2->addPipe(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

int Graph::findServicePointIdx(const std::string &in) const {
    return
}
