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

#define INF std::numeric_limits<int>::max()

/**
 * @brief Graph Class definition
 */
class Graph {

    struct PipeHash {
        std::size_t operator()(const std::pair<std::string, std::string>& p) const {
            std::size_t spAHash = std::hash<std::string>{}(p.first);
            std::size_t spBHash = std::hash<std::string>{}(p.second);
            return spAHash ^ (spBHash << 1);
        }
    };

    struct PipeEqual {
        bool operator()(const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };

public:
    ~Graph();

    void addReservoir(Reservoir *pReservoir);
    void addStation(Station *pStation);
    void addCity(City *pCity);

    void addServicePoint(ServicePoint *servicePoint);
    void removeServicePoint(ServicePoint *servicePoint);

    void addPipe(std::string spA, std::string spB, int capacity);
    void addBidirectionalPipe(std::string spA, std::string spB, int capacity);
    void removeAssociatedPipes(ServicePoint * servicePoint);
    void removePipe(Pipe * pipe);

    std::vector<ServicePoint *> getServicePointSet() const;
    std::vector<ServicePoint *> getReservoirSet() const;
    std::vector<ServicePoint *> getCitiesSet() const;
    std::vector<Pipe *> getPipeSet() const;

    Pipe * getPipeByEnds(std::string orig, std::string dest);
    ServicePoint * getCityByName(const std::string & name);
    ServicePoint * getReservoirByName(const std::string & name);
    ServicePoint * findServicePoint(const std::string &code) ;

protected:
    std::vector<ServicePoint *> servicePointSet;
    std::vector<ServicePoint *> reservoirSet;
    std::vector<ServicePoint *> citySet;
    std::vector<Pipe *> pipeSet;
    std::unordered_map<std::string,ServicePoint*> servicePointByCode;
    std::unordered_map<std::string,ServicePoint*> cityByName;
    std::unordered_map<std::string,ServicePoint*> reservoirByName;
    std::unordered_map<std::pair<std::string,std::string>,Pipe*, PipeHash, PipeEqual> pipeByEnds;
};

#endif //PROJECT1_GRAPH_H
