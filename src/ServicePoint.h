#ifndef PROJECT1_SERVICEPOINT_H
#define PROJECT1_SERVICEPOINT_H

#include "Pipe.h"
#include <vector>
#include <string>

class ServicePoint {
public:
    ServicePoint();

    Pipe * addPipe(Pipe * pipe);
    void removePipe(Pipe * pipe);
    void removeIncomingPipe(Pipe * pipe);
    void removeOutgoingPipes();

    std::vector<Pipe *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Pipe * getPred() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Pipe *path);

protected:
    std::vector<Pipe *> adj{};  // outgoing Pipes

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree = 0; // used by topsort
    double dist = 0;
    Pipe *pred = nullptr;
    std::string code;

    std::vector<Pipe *> incoming{}; // incoming Pipes

    void deletePipe(Pipe *Pipe);
};


#endif //PROJECT1_SERVICEPOINT_H

