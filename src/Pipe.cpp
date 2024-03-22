#include "Pipe.h"

Pipe::Pipe(std::string spA, std::string spB, int capacity, int direction): orig(codeToSP[spA]), dest(codeToSP[spB]), capacity(capacity)) {}

ServicePoint * Pipe::getDest() const {
    return this->dest;
}

double Pipe::getCapacity() const {
    return this->capacity;
}

ServicePoint * Pipe::getOrig() const {
    return this->orig;
}

Pipe *Pipe::getReverse() const {
    return this->reverse;
}

bool Pipe::isSelected() const {
    return this->selected;
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




