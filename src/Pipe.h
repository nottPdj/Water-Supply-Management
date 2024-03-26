#ifndef PROJECT1_PIPE_H
#define PROJECT1_PIPE_H

#include "ServicePoint.h"

class ServicePoint;

class Pipe {
public:
    Pipe(ServicePoint *orig, ServicePoint *dest, int capacity);

    ServicePoint * getOrig() ;
    ServicePoint * getDest() ;
    double getCapacity() const;
    Pipe * getReverse() const;
    double getFlow() const;

    bool isSelected() const;
    bool isOperational() const;
    bool isVisited() const;

    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
    void setOperational(bool b);
    void setVisited(bool visited);

protected:
    ServicePoint *orig;
    ServicePoint * dest; // destination ServicePoint

    double capacity; // Pipe weight, can also be used for capacity
    double flow;

    bool selected = false;
    bool operational=true;
    bool visited = false;

    Pipe *reverse = nullptr;
};


#endif //PROJECT1_PIPE_H
