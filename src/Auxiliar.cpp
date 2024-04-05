#include "Auxiliar.h"
#include "Reservoir.h"
#include "Station.h"
#include "City.h"
#include <sstream>
#include <fstream>
#include <algorithm>

/**
 * @brief Reads the DataSet
 * @param g
 * @param dataset
 */
void Auxiliar::readDataset(Graph *g, int dataset) {
    readReservoir(g, dataset);
    readStations(g, dataset);
    readCities(g, dataset);
    readPipes(g, dataset);
}


/**
 * @brief Reads the Reservoirs
 * @param g The main graph
 * @details Time Complexity O(n) n = number of reservoirs
 */
void Auxiliar::readReservoir(Graph *g, int dataset) {
    std::string files[2];
    files[0] = "../data/Project1DataSetSmall/Reservoirs_Madeira.csv";
    files[1] = "../data/Project1LargeDataSet/Reservoir.csv";
    std::ifstream file(files[dataset]);
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
        Reservoir* reservoir = new Reservoir(name, municipality, id, code, std::stoi(maxDelivery));
        g->addReservoir(reservoir);
    }

}

/**
 * @brief Reads the Stations
 * @param g The main graph
 * @details Time Complexity O(n) n = number of stations
 */
void Auxiliar::readStations(Graph *g, int dataset) {
    std::string files[2];
    files[0] = "../data/Project1DataSetSmall/Stations_Madeira.csv";
    files[1] = "../data/Project1LargeDataSet/Stations.csv";
    std::ifstream file(files[dataset]);
    std::string line;
    std::string id, code;
    getline(file, line);

    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, id, ',');
        getline(ss, code, '\r');
        Station* station = new Station(id, code);
        g->addStation(station);
    }

}

/**
 * @brief Reads the Cities
 * @param g The main graph
 * @details Time Complexity O(n) n = number of cities
 */
void Auxiliar::readCities(Graph *g, int dataset) {
    std::string files[2];
    files[0] = "../data/Project1DataSetSmall/Cities_Madeira.csv";
    files[1] = "../data/Project1LargeDataSet/Cities.csv";
    std::ifstream file(files[dataset]);
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
        std::replace(population.begin(),population.end(),'\"',' ');
        City* city = new City(name, id, code, std::stoi(demand), std::stoi(population));
        g->addCity(city);
    }

}

/**
 * @brief Reads the Pipes
 * @param g The main graph
 * @param dataset Time Complexity O(n) n = number of pipes
 */
void Auxiliar::readPipes(Graph *g, int dataset) {
    std::string files[2];
    files[0] = "../data/Project1DataSetSmall/Pipes_Madeira.csv";
    files[1] = "../data/Project1LargeDataSet/Pipes.csv";
    std::ifstream file(files[dataset]);
    std::string line;
    std::string servicePointA, servicePointB, capacity, direction;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, servicePointA, ',');
        getline(ss, servicePointB, ',');
        getline(ss, capacity, ',');
        getline(ss, direction, '\r');
        if (std::stoi(direction)){
            g->addPipe(servicePointA, servicePointB, std::stoi(capacity));
        }
        else {
            g->addBidirectionalPipe(servicePointA, servicePointB, std::stoi(capacity));
        }
    }

}
