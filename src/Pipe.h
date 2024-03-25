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


    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
    void setOperational(bool b);

protected:
    ServicePoint *orig;
    ServicePoint * dest; // destination ServicePoint

    double capacity; // Pipe weight, can also be used for capacity
    double flow;

    bool selected = false;
    bool operational=true;

    Pipe *reverse = nullptr;
};


#endif //PROJECT1_PIPE_H
