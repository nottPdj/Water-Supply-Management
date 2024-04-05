#ifndef PROJECT1_CITY_H
#define PROJECT1_CITY_H


#include "ServicePoint.h"

/**
 * @brief Service Point class definition
 *  @details Child Class of ServicePoint
 */
class City: public ServicePoint {
public:
    City(std::string name, std::string id, std::string code, int demand, int population);
    std::string getName();
    std::string getId();
    std::string getCode() const;
    int getDemand();
    int getPopulation();

private:
    std::string name;
    std::string id;
    std::string code;
    int demand;
    int population;

};


#endif //PROJECT1_CITY_H
