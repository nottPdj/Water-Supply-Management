//
// Created by pedro on 17-03-2024.
//

#include "Pipe.h"

Pipe<T>::Pipe(ServicePoint<T> *orig, ServicePoint<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

ServicePoint<T> * Pipe<T>::getDest() const {
    return this->dest;
}

double Pipe<T>::getWeight() const {
    return this->weight;
}

ServicePoint<T> * Pipe<T>::getOrig() const {
    return this->orig;
}

Pipe<T> *Pipe<T>::getReverse() const {
    return this->reverse;
}

bool Pipe<T>::isSelected() const {
    return this->selected;
}

double Pipe<T>::getFlow() const {
    return flow;
}

void Pipe<T>::setSelected(bool selected) {
    this->selected = selected;
}

void Pipe<T>::setReverse(Pipe<T> *reverse) {
    this->reverse = reverse;
}

void Pipe<T>::setFlow(double flow) {
    this->flow = flow;
}