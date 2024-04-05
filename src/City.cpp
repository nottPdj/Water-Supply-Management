#include "City.h"

/**
 * @brief City Constructor
 * @param name
 * @param id
 * @param code
 * @param demand
 * @param population
 */
City::City(std::string name, std::string id, std::string code, int demand, int population): name(name), id(id), code(code), demand(demand), population(population) {}

/**
 * @brief Gets the City name
 * @return name
 */
std::string City::getName() {
    return this->name;
}
/**
 * @brief Gets the City id
 * @return id
 */
std::string City::getId() {
    return this->id;
}

/**
 * @brief Gets the City Code
 * @return code
 */
std::string City::getCode() const {
    return this->code;
}

/**
 * @brief Gets the City demand
 * @return demand
 */
int City::getDemand() {
    return this->demand;
}

/**
 * @brief Gets the City population
 * @return population
 */
int City::getPopulation() {
    return this->population;
}
