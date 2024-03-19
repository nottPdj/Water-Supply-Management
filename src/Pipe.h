//
// Created by pedro on 17-03-2024.
//

#ifndef PROJECT1_PIPE_H
#define PROJECT1_PIPE_H


#include "ServicePoint.h"

class Pipe {
public:

    Pipe(std::string spA, std::string spB, int capacity, int direction);

    ServicePoint * getDest() const;
    double getCapacity() const;
    int getDirection();
    bool isSelected() const;
    ServicePoint * getOrig() const;
    Pipe *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
protected:
    ServicePoint * dest; // destination ServicePoint
    double capacity; // Pipe weight, can also be used for capacity
    int direction;
    // auxiliary fields
    bool selected = false;

    // used for bidirectional Pipes
    ServicePoint *orig;
    Pipe *reverse = nullptr;

    double flow; // for flow-related problems
};


#endif //PROJECT1_PIPE_H
