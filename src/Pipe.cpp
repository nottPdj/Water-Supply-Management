//
// Created by pedro on 17-03-2024.
//

#include "Pipe.h"

Pipe::Pipe(ServicePoint *orig, ServicePoint *dest, double w): orig(orig), dest(dest), weight(w) {}

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