#include "City.h"

City::City(std::string name, std::string id, std::string code, int demand, int population): name(name), id(id), code(code), demand(demand), population(population) {}

std::string City::getName() {
    return this->name;
}

std::string City::getId() {
    return this->id;
}

std::string City::getCode() const {
    return this->code;
}

int City::getDemand() {
    return this->demand;
}

int City::getPopulation() {
    return this->population;
}
