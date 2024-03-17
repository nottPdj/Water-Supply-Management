//
// Created by pedro on 17-03-2024.
//

#ifndef PROJECT1_SERVICEPOINT_H
#define PROJECT1_SERVICEPOINT_H

#include "Pipe.h"
#include <vector>
#include <string>

class ServicePoint {
public:
    ServicePoint();
    bool operator<(ServicePoint & ServicePoint) const; // // required by MutablePriorityQueue

    std::string getInfo() const;
    std::vector<Pipe *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Pipe *getPath() const;
    std::vector<Pipe *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Pipe *path);
    Pipe * addPipe(ServicePoint *dest, double w);
    bool removePipe(T in);
    void removeOutgoingPipes();

    friend class MutablePriorityQueue<ServicePoint>;
protected:
    std::vector<Pipe *> adj{};  // outgoing Pipes

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree{}; // used by topsort
    double dist = 0;
    Pipe *path = nullptr;

    std::vector<Pipe *> incoming{}; // incoming Pipes

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deletePipe(Pipe *Pipe);
};


#endif //PROJECT1_SERVICEPOINT_H
