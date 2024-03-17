#include "Auxiliar.h"
#include "Reservoir.h"
#include "Station.h"
#include "City.h"
#include <sstream>
#include <fstream>

/**
 * @brief Reads the airports
 * @param g The main graph
 * @details Time Complexity O(n) n = number of airports
 */
void Auxiliar::readReservoir(Graph &g) {
    std::ifstream file("../data/Project1DataSetSmall/Reservoirs_Madeira.csv");
    std::string line;
    std::string name, municipality, id, code, maxDelivery;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, name, ',');
        getline(ss, municipality, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, maxDelivery, '\r');
        Reservoir* reservoir = new Reservoir(name, municipality, id, code, stoi(maxDelivery));
        g.addReservoir(reservoir);
    }

}

/**
 * @brief Reads the airlines
 * @param g The main graph
 * @details Time Complexity O(n) n = number of airlines
 */
void Auxiliar::readStations(Graph &g) {
    std::ifstream file("../data/Project1DataSetSmall/Stations_Madeira.csv");
    std::string line;
    std::string id, code;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, id, ',');
        getline(ss, code, '\r');
        Station* station = new Station(id, code);
        g.addStation(station);
    }

}

/**
 * @brief Reads the flights
 * @param g The main graph
 * @details Time Complexity O(n) n = number of flights
 */
void Auxiliar::readCities(Graph &g) {
    std::ifstream file("../data/Project1DataSetSmall/Cities_Madeira.csv");
    std::string line;
    std::string name, id, code, demand, population;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, demand, ',');
        getline(ss, population, '\r');
        City* city = new City(name, id, code, stoi(demand), stoi(population));
        g.addCity(city);
    }

}
