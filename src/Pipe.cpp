#include "Pipe.h"

Pipe::Pipe(ServicePoint *orig, ServicePoint *dest, int capacity): orig(orig), dest(dest), capacity(capacity) {}

ServicePoint * Pipe::getDest()  {
    return this->dest;
}

double Pipe::getCapacity() const {
    return this->capacity;
}

ServicePoint * Pipe::getOrig()  {
    return this->orig;
}

Pipe *Pipe::getReverse() const {
    return this->reverse;
}

bool Pipe::isSelected() const {
    return this->selected;
}

bool Pipe::isVisited() const {
    return this->visited;
}

double Pipe::getFlow() const {
    return flow;
}

void Pipe::setSelected(bool selected) {
    this->selected = selected;
}

void Pipe::setReverse(Pipe *reverse) {
    this->reverse = reverse;
}

void Pipe::setFlow(double flow) {
    this->flow = flow;
}

void Pipe::setOperational(bool b) {
    operational=b;
}

void Pipe::setVisited(bool visited) {
    this->visited = visited;
}

bool Pipe::isOperational() const {
    return operational;
}




