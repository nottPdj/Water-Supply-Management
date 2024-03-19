#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <vector>
#include <unordered_map>
#include <limits>
#include "ServicePoint.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "Station.h"
#include "City.h"

#define INF std::numeric_limits<double>::max()

class Graph {
public:
    ~Graph();

    void addReservoir(Reservoir *pReservoir);
    void addStation(Station *pStation);
    void addCity(City *pCity);

    void addServicePoint(ServicePoint *servicePoint);
    void removeServicePoint(ServicePoint *servicePoint);


    void addPipe(Pipe *pPipe);
    void addBidirectionalPipe(Pipe * pPipe1, Pipe * pPipe2);
    void removePipe(Pipe * pipe);

    int getNumServicePoint() const;
    std::vector<ServicePoint *> getServicePointSet() const;
    std::vector<ServicePoint *> getReservoirSet() const;
    std::vector<ServicePoint *> getCitiesSet() const;

    ServicePoint * getCityByName(const std::string & name);
    ServicePoint * getReservoirByName(const std::string & name);
    ServicePoint * findServicePoint(const std::string &code) ;

protected:
    std::vector<ServicePoint *> servicePointSet;    // ServicePoint set
    std::vector<ServicePoint *> reservoirSet;
    std::vector<ServicePoint *> citySet;
    std::unordered_map<std::string,ServicePoint*> servicePointByCode;
    std::unordered_map<std::string,ServicePoint*> cityByName;
    std::unordered_map<std::string,ServicePoint*> reservoirByName;
};

#endif //PROJECT1_GRAPH_H

