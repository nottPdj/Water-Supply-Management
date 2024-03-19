#include "Graph.h"


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

void Graph::removeServicePoint(ServicePoint *servicePoint) {
    // TODO
}


void Graph::addPipe(Pipe *pPipe) {
    pPipe->getOrig()->addPipe(pPipe);
}

void Graph::addBidirectionalPipe(Pipe *pPipe1, Pipe *pPipe2) {
    pPipe1->getOrig()->addPipe(pPipe1);
    pPipe2->getOrig()->addPipe(pPipe2);
    pPipe1->setReverse(pPipe2);
    pPipe2->setReverse(pPipe1);
}

void Graph::removePipe(const int &source, const int &dest) {
    // TODO
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


ServicePoint * getCityByName(const std::string &name){
    return cityByName[name];
}

ServicePoint * getReservoirByName(const std::string &name){
    return reservoirByName[name];
}

ServicePoint * Graph::findServicePoint(const std::string &code) {
    return servicePointByCode[code];
}
