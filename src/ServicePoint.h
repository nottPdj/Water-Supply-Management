#ifndef PROJECT1_SERVICEPOINT_H
#define PROJECT1_SERVICEPOINT_H

#include "Pipe.h"
#include <vector>
#include <string>

class Pipe;

/**
 * @brief Service Point class definition
 */

class ServicePoint {
public:
    ServicePoint();

    virtual std::string getCode() const = 0;

    void addPipe(Pipe * pipe);
    void addIncomingPipe(Pipe * pipe);
    void removeIncomingPipe(Pipe * pipe);
    void removeOutgoingPipe(Pipe * pipe);

    std::vector<Pipe *> getIncoming() const;

    std::vector<Pipe *> getAdj() const;
    bool isVisited() const;
    bool isOperational() const;
    Pipe* getPath() const;
    Pipe * getPred() const;

    void setVisited(bool visited);
    void setPath(Pipe *path);
    void setPred(Pipe * pred);
    void setOperational(bool b);


protected:
    std::vector<Pipe *> adj{};  // outgoing Pipes

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    std::string code;
    bool operational=true;


    std::vector<Pipe *> incoming{}; // incoming Pipes
    Pipe* path=nullptr;
    void deletePipe(Pipe *Pipe);
};


#endif //PROJECT1_SERVICEPOINT_H

