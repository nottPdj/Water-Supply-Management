#ifndef PROJECT1_STATION_H
#define PROJECT1_STATION_H


#include "ServicePoint.h"

/**
 * @brief Station Class definition
 * @details Child Class of ServicePoint
 */
class Station: public ServicePoint {
public:
    Station(std::string id, std::string code);
    std::string getId();
    std::string getCode() const;

private:
    std::string id;
    std::string code;
};


#endif //PROJECT1_STATION_H
