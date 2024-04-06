#ifndef PROJECT1_RESERVOIR_H
#define PROJECT1_RESERVOIR_H


#include "ServicePoint.h"

/**
 * @brief Reservoir Class definition
 * @details Child Class of ServicePoint
 */
class Reservoir: public ServicePoint {
public:
    Reservoir(std::string name, std::string municipality, std::string id, std::string code, int maxDelivery);
    std::string getName();
    std::string getMunicipality();
    std::string getId();
    std::string getCode() const;
    int getMaxDelivery();

private:
    std::string name;
    std::string municipality;
    std::string id;
    std::string code;
    int maxDelivery;
};

#endif //PROJECT1_RESERVOIR_H
