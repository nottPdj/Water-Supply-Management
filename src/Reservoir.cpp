#include "Reservoir.h"

/**
 * @brief Reservoir Constructor
 * @param name
 * @param municipality
 * @param id
 * @param code
 * @param maxDelivery
 */
Reservoir::Reservoir(std::string name,std::string  municipality, std::string id, std::string code, int maxDelivery):
        name(name), municipality(municipality), id(id), code(code), maxDelivery(maxDelivery) {}

/**
 * @brief Gets the Reservoir name
 * @return name
 */
std::string Reservoir::getName() {
    return this->name;
}

/**
 * @brief Gets the Reservoir municipality
 * @return municipality
 */
std::string Reservoir::getMunicipality() {
    return this->municipality;
}

/**
 * @brief Gets the Reservoir id
 * @return id
 */
std::string Reservoir::getId() {
    return this->id;
}

/**
 * @brief Gets the Reservoir code
 * @return code
 */
std::string Reservoir::getCode() const {
    return this->code;
}

/**
 * @brief Gets the maximum delivery of a Reservoir
 * @return maxDelivery
 */
int Reservoir::getMaxDelivery() {
    return this->maxDelivery;
}
