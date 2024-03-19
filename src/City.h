#ifndef PROJECT1_CITY_H
#define PROJECT1_CITY_H


#include "ServicePoint.h"

class City: private ServicePoint {
public:
    City(std::string name, std::string id, std::string code, int demand, int population);
private:
    std::string name;
    std::string id;
    std::string code;
    int demand;
    int population;

};


#endif //PROJECT1_CITY_H
