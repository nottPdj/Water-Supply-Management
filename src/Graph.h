#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <vector>
#include <unordered_map>
#include "ServicePoint.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "Station.h"
#include "City.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a ServicePoint with a given the content.
    */
    ServicePoint *findServicePoint(const T &in) const;
    /*
     *  Adds a ServicePoint with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a ServicePoint with that content already exists.
     */
    bool addServicePoint(const T &in);
    bool removeServicePoint(const T &in);

    /*
     * Adds an Pipe to a graph (this), given the contents of the source and
     * destination vertices and the Pipe weight (w).
     * Returns true if successful, and false if the source or destination ServicePoint does not exist.
     */
    bool addPipe(const int &sourc, const int &dest, double w);
    bool removePipe(const int &source, const int &dest);
    bool addBidirectionalPipe(const int &sourc, const int &dest, double w);

    int getNumServicePoint() const;
    std::vector<ServicePoint *> getServicePointSet() const;

    std:: vector<> dfs() const;
    std:: vector<> dfs(const int & source) const;
    void dfsVisit(ServicePoint<T> *v,  std::vector<T> & res) const;
    std::vector<> bfs(const int & source) const;

    bool isDAG() const;
    bool dfsIsDAG(ServicePoint<T> *v) const;
    std::vector<> topsort() const;

    void addReservoir(Reservoir *pReservoir);

    void addStation(Station *pStation);

    void addCity(City *pCity);

protected:
    std::vector<ServicePoint *> ServicePointSet;    // ServicePoint set
    std::vector<int> citiesFlow;
    std::unordered_map<std::string,ServicePoint*> servicePointName;
    /*
     * Finds the index of the ServicePoint with a given content.
     */
    int findServicePointIdx(const std::string &in) const;
};

#endif //PROJECT1_GRAPH_H
