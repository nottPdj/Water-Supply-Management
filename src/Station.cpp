#include "Station.h"

/**
 * @brief Station Constructor
 * @param id
 * @param code
 */
Station::Station(std::string id, std::string code): id(id), code(code) {}

/**
 * @brief Gets the Station id
 * @return id
 */
std::string Station::getId() {
    return this->id;
}

/**
 * @brief Gets the Station Code
 * @return code
 */
std::string Station::getCode() const {
    return this->code;
}
