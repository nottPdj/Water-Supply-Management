#include "Reservoir.h"

Reservoir::Reservoir(std::string name,std::string  municipality, std::string id, std::string code, int maxDelivery):
        name(name), municipality(municipality), id(id), code(code), maxDelivery(maxDelivery) {}

std::string Reservoir::getName() {
    return this->name;
}

std::string Reservoir::getMunicipality() {
    return this->municipality;
}

std::string Reservoir::getId() {
    return this->id;
}

std::string Reservoir::getCode() {
    return this->code;
}

int Reservoir::getMaxDelivery() {
    return this->maxDelivery;
}
