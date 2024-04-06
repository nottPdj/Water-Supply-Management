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

    void setVisited(bool visited);
    void setPath(Pipe *path);
    void setOperational(bool b);

protected:
    std::string code;
    std::vector<Pipe *> adj{}; // outgoing Pipes
    std::vector<Pipe *> incoming{}; // incoming Pipes

    // auxiliary fields
    bool visited = false;
    bool operational=true;

    Pipe* path=nullptr;
};

#endif //PROJECT1_SERVICEPOINT_H
