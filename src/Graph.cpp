#include <iostream>
#include <algorithm>
#include "Graph.h"

Graph::~Graph() {
    // TODO check if destroys everything
    auto it = servicePointSet.begin();
    while (it != servicePointSet.end()) {
        ServicePoint *sp = *it;
        it++;
        removeServicePoint(sp);
    }
}

void Graph::addReservoir(Reservoir *pReservoir) {
    addServicePoint(pReservoir);
    reservoirSet.push_back(pReservoir);
    reservoirByName.insert(make_pair(pReservoir->getName(), pReservoir));

}

void Graph::addStation(Station *pStation) {
    addServicePoint(pStation);

}

void Graph::addCity(City *pCity) {
    addServicePoint(pCity);
    citySet.push_back(pCity);
    cityByName.insert(make_pair(pCity->getName(), pCity));
}


void Graph::addServicePoint(ServicePoint *servicePoint) {
    servicePointSet.push_back(servicePoint);
    servicePointByCode.insert(make_pair(servicePoint->getCode(), servicePoint));
}

// Usar pra remover service point
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

void Graph::removeAssociatedPipes(ServicePoint * servicePoint) {
    for (Pipe * pipe : servicePoint->getAdj()) {
        removePipe(pipe);
    }
    for (Pipe * pipe : servicePoint->getIncoming()) {
        removePipe(pipe);
    }
}

void Graph::addPipe(std::string spA, std::string spB, int capacity) {
    Pipe *pPipe = new Pipe(servicePointByCode[spA], servicePointByCode[spB], capacity);
    pPipe->getOrig()->addPipe(pPipe);
    pPipe->getDest()->addIncomingPipe(pPipe);
    pipeSet.push_back(pPipe);
    pipeByEnds[std::make_pair(spA,spB)] = {pPipe};
}

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

// Usar pra remover pipes
void Graph::removePipe(Pipe * pipe) {
    pipe->getOrig()->removeOutgoingPipe(pipe);
    pipe->getDest()->removeIncomingPipe(pipe);
    // TODO modificado verificar se funciona
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


int Graph::getNumServicePoint() const {
    return servicePointSet.size();
}

std::vector<ServicePoint *> Graph::getServicePointSet() const {
    return servicePointSet;
}

std::vector<ServicePoint *> Graph::getReservoirSet() const{
    return reservoirSet;
}

std::vector<ServicePoint *> Graph::getCitiesSet() const{
    return citySet;
}

std::vector<Pipe *> Graph::getPipeSet() const{
    return pipeSet;
}

ServicePoint * Graph::getCityByName(const std::string &name){
    return cityByName[name];
}

ServicePoint * Graph::getReservoirByName(const std::string &name){
    return reservoirByName[name];
}

ServicePoint * Graph::findServicePoint(const std::string &code) {
    return servicePointByCode[code];
}

Pipe * Graph::getPipeByEnds(std::string orig, std::string dest){
    return pipeByEnds[std::make_pair(orig,dest)];
}
