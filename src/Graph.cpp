#include <iostream>
#include <algorithm>
#include "Graph.h"

/**
 * @brief Graph Destructor
 * @details Time Complexity O(S) S = number of ServicePoints
 */
Graph::~Graph() {
    auto it = servicePointSet.begin();
    while (it != servicePointSet.end()) {
        ServicePoint *sp = *it;
        it++;
        removeServicePoint(sp);
    }
}

/**
 * @brief Adds a Reservoir to the Graph
 * @param pReservoir
 */
void Graph::addReservoir(Reservoir *pReservoir) {
    addServicePoint(pReservoir);
    reservoirSet.push_back(pReservoir);
    reservoirByName.insert(make_pair(pReservoir->getName(), pReservoir));

}

/**
 * @brief Adds a Station to the Graph
 * @param pStation
 */
void Graph::addStation(Station *pStation) {
    addServicePoint(pStation);

}

/**
 * @brief Adds a City to the Graph
 * @param pCity
 */
void Graph::addCity(City *pCity) {
    addServicePoint(pCity);
    citySet.push_back(pCity);
    cityByName.insert(make_pair(pCity->getName(), pCity));
}

/**
 * @brief Adds a ServicePoint to the Graph
 * @param servicePoint
 */
void Graph::addServicePoint(ServicePoint *servicePoint) {
    servicePointSet.push_back(servicePoint);
    servicePointByCode.insert(make_pair(servicePoint->getCode(), servicePoint));
}

/**
 * @brief Removes a Service Point from the Graph
 * @param servicePoint
 * @details Time Complexity O(P²) P = number of Pipes
 */
void Graph::removeServicePoint(ServicePoint *servicePoint) {
    removeAssociatedPipes(servicePoint);
    servicePointByCode.erase(servicePoint->getCode());
    servicePointSet.erase(std::find(servicePointSet.begin(), servicePointSet.end(), servicePoint));
    City * c = dynamic_cast<City *> (servicePoint);
    Reservoir * r = dynamic_cast<Reservoir *> (servicePoint);
    Station * s = dynamic_cast<Station *> (servicePoint);
    if (c != nullptr) {
        citySet.erase(std::find(citySet.begin(), citySet.end(), servicePoint));
        cityByName.erase(c->getName());
    } else if (r != nullptr) {
        reservoirSet.erase(std::find(reservoirSet.begin(), reservoirSet.end(), servicePoint));
        reservoirByName.erase(r->getName());
    }
    delete servicePoint;
}

/**
 * @brief Removes associated Pipes to a given Service Point
 * @param servicePoint
 * @details Time Complexity O(P²) P = bigger number of adjacent or incoming Pipes
 */
void Graph::removeAssociatedPipes(ServicePoint * servicePoint) {
    for (Pipe * pipe : servicePoint->getAdj()) {
        removePipe(pipe);
    }
    for (Pipe * pipe : servicePoint->getIncoming()) {
        removePipe(pipe);
    }
}

/**
 * @brief Adds a Pipe to the Graph
 * @param spA
 * @param spB
 * @param capacity
 */
void Graph::addPipe(std::string spA, std::string spB, int capacity) {
    Pipe *pPipe = new Pipe(servicePointByCode[spA], servicePointByCode[spB], capacity);
    pPipe->getOrig()->addPipe(pPipe);
    pPipe->getDest()->addIncomingPipe(pPipe);
    pipeSet.push_back(pPipe);
    pipeByEnds[std::make_pair(spA,spB)] = {pPipe};
}

/**
 * @brief Adds a Bidirectional Pipe to the Graph
 * @param spA
 * @param spB
 * @param capacity
 */
void Graph::addBidirectionalPipe(std::string spA, std::string spB, int capacity) {
    Pipe *pPipe1 = new Pipe(servicePointByCode[spA], servicePointByCode[spB], capacity);
    Pipe *pPipe2 = new Pipe(servicePointByCode[spB], servicePointByCode[spA], capacity);
    pPipe1->getOrig()->addPipe(pPipe1);
    pPipe1->getDest()->addIncomingPipe(pPipe1);
    pPipe2->getOrig()->addPipe(pPipe2);
    pPipe2->getDest()->addIncomingPipe(pPipe2);
    pPipe1->setReverse(pPipe2);
    pPipe2->setReverse(pPipe1);
    pipeSet.push_back(pPipe1);
    pipeSet.push_back(pPipe2);
    pipeByEnds[std::make_pair(spA,spB)] = {pPipe1};
    pipeByEnds[std::make_pair(spB,spA)] = {pPipe2};
}

/**
 * @brief Removes a Pipe from the Graph
 * @param pipe
 * @details Time Complexity O(P) P = number of Pipes
 */
void Graph::removePipe(Pipe * pipe) {
    pipe->getOrig()->removeOutgoingPipe(pipe);
    pipe->getDest()->removeIncomingPipe(pipe);
    if (pipe->getReverse() != nullptr) {
        pipe->getReverse()->getOrig()->removeOutgoingPipe(pipe->getReverse());
        pipe->getReverse()->getDest()->removeIncomingPipe(pipe->getReverse());
        pipeSet.erase(std::find(pipeSet.begin(), pipeSet.end(), pipe->getReverse()));
        pipeByEnds.erase(std::make_pair(pipe->getDest()->getCode(),pipe->getOrig()->getCode()));
        delete pipe->getReverse();
    }
    pipeSet.erase(std::find(pipeSet.begin(), pipeSet.end(), pipe));
    pipeByEnds.erase(std::make_pair(pipe->getOrig()->getCode(),pipe->getDest()->getCode()));
    delete pipe;
}

/**
 * @brief Gets the ServicePoint set
 * @return servicePointSet
 */
std::vector<ServicePoint *> Graph::getServicePointSet() const {
    return servicePointSet;
}

/**
 * @brief Gets the Reservoir set
 * @return reservoirSet
 */
std::vector<ServicePoint *> Graph::getReservoirSet() const{
    return reservoirSet;
}

/**
 * @brief Gets the Cities set
 * @return citySet
 */
std::vector<ServicePoint *> Graph::getCitiesSet() const{
    return citySet;
}

/**
 * @brief Gets the Pipe set
 * @return pipeSet
 */
std::vector<Pipe *> Graph::getPipeSet() const{
    return pipeSet;
}

/**
 * @brief Gets the City by name
 * @param name
 */
ServicePoint * Graph::getCityByName(const std::string &name){
    return cityByName[name];
}

/**
 * @brief Gets the Reservoir by name
 * @param name
 */
ServicePoint * Graph::getReservoirByName(const std::string &name){
    return reservoirByName[name];
}

/**
 * @brief Gets the ServicePoint by code
 * @param code
 */
ServicePoint * Graph::findServicePoint(const std::string &code) {
    return servicePointByCode[code];
}

/**
 * @brief Gets the Pipe by its ends
 * @param orig
 * @param dest
 */
Pipe * Graph::getPipeByEnds(std::string orig, std::string dest){
    return pipeByEnds[std::make_pair(orig,dest)];
}
