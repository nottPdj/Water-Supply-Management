#include "Station.h"

Station::Station(std::string id, std::string code): id(id), code(code) {}

std::string Station::getId() {
    return this->id;
}

std::string Station::getCode() {
    return this->code;
}
