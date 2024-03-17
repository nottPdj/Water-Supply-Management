//
// Created by pedro on 17-03-2024.
//

#ifndef PROJECT1_STATION_H
#define PROJECT1_STATION_H


#include "ServicePoint.h"

class Station: private ServicePoint {
public:
    Station(std::string id, std::string code);

private:
    std::string id;
    std::string code;
};


#endif //PROJECT1_STATION_H
