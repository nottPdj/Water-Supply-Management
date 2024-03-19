#ifndef PROJECT1_PIPE_H
#define PROJECT1_PIPE_H


#include "ServicePoint.h"

class Pipe {
public:
    Pipe(std::string spA, std::string spB, int capacity, int direction);

    ServicePoint * getOrig() const;
    ServicePoint * getDest() const;
    double getCapacity() const;
    Pipe * getReverse() const;
    double getFlow() const;

    bool isSelected() const;

    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
protected:
    ServicePoint *orig;
    ServicePoint * dest; // destination ServicePoint

    double capacity; // Pipe weight, can also be used for capacity
    double flow;

    bool selected = false;

    Pipe *reverse = nullptr;
};


#endif //PROJECT1_PIPE_H
