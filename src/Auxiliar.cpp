#include "Auxiliar.h"
#include <sstream>
#include <fstream>

/**
 * @brief Reads the airports
 * @param g The main graph
 * @details Time Complexity O(n) n = number of airports
 */
void Auxiliar::readAirports(Graph &g) {
    std::ifstream file("../airports.csv");
    std::string line;
    std::string code, name, city, country, latitude, longitude;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, '\r');
        Airport* airport = new Airport(code, name, city, country, latitude, longitude);
        g.addAirport(airport);
    }

}

/**
 * @brief Reads the airlines
 * @param g The main graph
 * @details Time Complexity O(n) n = number of airlines
 */
void Auxiliar::readAirlines(Graph &g) {
    std::ifstream file("../airlines.csv");
    std::string line;
    std::string code, name, callsign, country;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, '\r');
        Airline* airline = new Airline(code, name, callsign, country);
        g.addAirline(airline);
    }

}

/**
 * @brief Reads the flights
 * @param g The main graph
 * @details Time Complexity O(n) n = number of flights
 */
void Auxiliar::readFlights(Graph &g) {
    std::ifstream file("../flights.csv");
    std::string line;
    std::string source, dest, airline;

    getline(file, line);
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, source, ',');
        getline(ss, dest, ',');
        getline(ss, airline, '\r');
        Flight flight(g.getAirport(source), g.getAirport(dest), g.getAirline(airline));
        g.addFlight(flight);
    }

}
