#ifndef PROJECT1_SERVICEPOINT_H
#define PROJECT1_SERVICEPOINT_H

#include "Pipe.h"
#include <vector>
#include <string>

class Pipe;

class ServicePoint {
public:
    ServicePoint();

    virtual std::string getCode() const = 0;

    void addPipe(Pipe * pipe);
    void addIncomingPipe(Pipe * pipe);
    void removePipe(Pipe * pipe);
    void removeIncomingPipe(Pipe * pipe);
    void removeOutgoingPipe(Pipe * pipe);
    void removeOutgoingPipes();
    void removeIncomingPipes();
    void removeAssociatedPipes();
    std::vector<Pipe *> getIncoming() const;

    std::vector<Pipe *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    bool isOperational() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Pipe* getPath() const;
    Pipe * getPred() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Pipe *path);
    void setPred(Pipe * pred);
    void setOperational(bool b);


protected:
    std::vector<Pipe *> adj{};  // outgoing Pipes

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree = 0; // used by topsort
    double dist = 0;
    Pipe *pred = nullptr;
    std::string code;
    bool operational=true;


    std::vector<Pipe *> incoming{}; // incoming Pipes
    Pipe* path=nullptr;
    void deletePipe(Pipe *Pipe);
};


#endif //PROJECT1_SERVICEPOINT_H

