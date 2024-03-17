#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "Menu.h"


/**
 * @brief Constructor of the Menu class. Stores the graph containing all air travel information in the private field
 * so that it can communicate with it throughout the program.
 * @param g Graph containing all air travel information being managed by the Menu
 */
Menu::Menu(const Management &m) {
    this->m = m;
}

/**
 * @brief This method is called to start the interface.
 */
void Menu::run(){
    system("clear");
    printMainMenu();
    system("clear");
}

/**
 * @brief Prints the main menu.
 */
void Menu::printMainMenu() {
    system("clear");
    std::cout << center("WATER SUPPLY MANAGEMENT", '*', MENU_WIDTH) << "\n\n"
              << "Basic Service Metrics" << "\n"
              << "\tMaximum amount of water that can reach:" << "\n"
              << "\t\t0 - each city" << "\n"
              << "\t\t1 - a city" << "\n"
              << "\t2 - Check if current network configuration meets the water needs of all customers" << "\n"
              << "\t3 - Balance the load across the network" << "\n"
              << "Reliability and Sensitivity to Failures" << "\n"
              << "\t4 - Water Reservoir unavailable" << "\n"
              << "\t5 - Pumping Station unavailable" << "\n"
              << "\t6 - Crucial pipelines" << "\n\n";

    printExit();
    std::cout << "Press the number corresponding the action you want." << "\n";
    waitMenu();
}

/**
 * @brief Waits for the input and depending on it, calls the method responsible for accomplishing what was asked.
 */
void Menu::waitMenu(){
    std::string choice;
    std::cin >> choice;             // Fetch the option chosen
    if (choice == "q")              // Quit
        return;
    system("clear");
    printingOptions options;
    switch (stoi(choice)) {
        // Global numbers
        case 0: {
            std::cout << "Global numbers\n\n";
            std::cout << "There are " + std::to_string(g.getNumAirports()) + " airports\n";
            std::cout << "There are " + std::to_string(g.getNumFlights()) + " flights\n";
            std::cout << "There are " + std::to_string(g.getNumAirlines()) + " airlines\n";
            std::cout << "\n\n";
            endDisplayMenu();
            getInput();
            break;
        }
            // Flights from an airport
        case 1: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            system("clear");
            std::pair<int, int> nums = g.getNumFlightsFromAirport(code);
            std::cout << "There are " + std::to_string(nums.first) + " flights from airport " + code + "\n";
            std::cout << "From " + std::to_string(nums.second) + " different airlines\n";
            std::cout << "\n\n";
            endDisplayMenu();
            getInput();
            break;
        }
            // Flights per city
        case 2: {
            std::cout << "Enter the city name: ";
            std::string city;
            std::getline(std::cin >> std::ws, city);        // Fetch city
            std::cout << "Enter the country name: ";
            std::string country;
            std::getline(std::cin >> std::ws, country);        // Fetch country
            std::pair<std::string, std::string> cityCountry = {city, country};
            system("clear");
            std::cout << "There are " + std::to_string(g.getNumFlightsFromCity(cityCountry)) + " flights from " + city + ", " + country + "\n";
            std::cout << "\n\n";
            endDisplayMenu();
            getInput();
            break;
        }
            // Flights per airline
        case 3: {
            std::cout << "Enter the airline code: ";
            std::string airline;
            std::cin >> airline;        // Fetch airline
            system("clear");
            std::cout << "There are " + std::to_string(g.getNumFlightsPerAirline(airline)) + " flights from " + airline + "\n";
            std::cout << "\n\n";
            endDisplayMenu();
            getInput();
            break;
        }
            // Countries that a city flies to directly
        case 4: {
            std::cout << "Enter the city name: ";
            std::string city;
            std::getline(std::cin >> std::ws, city);
            std::cout << "Enter the country name: ";
            std::string country;
            std::getline(std::cin >> std::ws, country);
            std::pair<std::string, std::string> cityCountry = {city, country};
            options.message = "Countries that " + city + ", " + country + " flies to\n";
            printCountriesList(g.getCountriesFromCity(cityCountry), options);
            break;
        }
            // Direct destinations from an airport
        case 5: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            getDestinations(code);
            break;
        }
            // All possible destinations from an airport
        case 6: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            getDestinations(code, INT32_MAX);
            break;
        }
            // Reachable destinations from an airport in a maximum n lay-overs
        case 7: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            std::cout << "Enter the maximum number of lay-overs: ";
            int stops;
            std::cin >> stops;        // Fetch max number of lay-overs
            getDestinations(code, stops);
            break;
        }
            // Maximum trip (with the greatest number of lay-overs)
        case 8: {
            options.sort = false;
            options.showSortingOptions = false;
            options.printCountMessage = false;
            int stops;
            std::vector<std::pair<Airport *, Airport *>> maxTrips = g.getMaxTrip(stops);
            options.message = "Maximum trips available:\n";
            options.message += "There are " + std::to_string(maxTrips.size()) + " trips with the greatest number of lay-overs (" + std::to_string(stops) + ")\n";
            printSourceDestList(maxTrips, options);
            break;
        }
            // Airports with the greatest air traffic capacity
        case 9: {
            std::cout << "Display Top-";
            int top;
            std::cin >> top;
            options.message = "Top-" + std::to_string(top) + " airports with the greatest air traffic capacity\n";
            options.printCountMessage = false;
            options.sortOptions.orderBy = 6;
            options.sortOptions.ascending = false;
            options.showSortingOptions = false;
            printAirportsList(g.getGreatestNumFlights(top), options);
            break;
        }
            // Essential airports to the network’s circulation capability
        case 10: {
            options.message = "Essential airports to the network's circulation capability\n";
            printAirportsList(g.getEssentialAirports(), options);
            break;
        }
            // Consult the best flight option
        case 11: {
            std::cout << "FROM\n";
            std::cout << "Search by: \n"
                      << "\t0 - Airport code\n"
                      << "\t1 - Airport name\n"
                      << "\t2 - City (\"city,country\")\n"
                      << "\t3 - Geographical coordinates (\"lat,lon\")\n";
            int searchFrom;
            std::string source;
            std::cin >> searchFrom;
            std::cout << "\nFrom: ";
            std::getline(std::cin >> std::ws, source);

            std::cout << "\nTO\n";
            std::cout << "Search by: \n"
                      << "\t0 - Airport code\n"
                      << "\t1 - Airport name\n"
                      << "\t2 - City (\"city,country\")\n"
                      << "\t3 - Geographical coordinates (\"lat,lon\")\n";
            int searchTo;
            std::string dest;
            std::cin >> searchTo;
            std::cout << "\nTo: ";
            std::getline(std::cin >> std::ws, dest);
            system("clear");

            options.message = "Best flight option(s) from " + source + " to " + dest;
            std::cout << "From " << source << " to " << dest << "\n\n";

            std::cout << "Airline Preferences\n"
                      << "\t0 - Maximum number of different airlines\n"
                      << "\t1 - Travel only in specific airlines\n"
                      << "\t2 - No preferences\n";
            int preference = 2;
            std::cin >> preference;

            int maxAirlines = -1;
            std::vector<std::string> airlineCodes;

            if (preference == 0) {
                std::cout << "Maximum number of different airlines: ";
                std::cin >> maxAirlines;
                options.message += " in a maximum of " + std::to_string(maxAirlines) + " airlines";
            } else if (preference == 1) {
                std::cout << "List the airlines to use by code (Separated by ENTER, 'done' when all are listed): \n";
                std::string airline;
                while (true) {
                    std::cin >> airline;
                    if (airline == "done") {
                        break;
                    }
                    airlineCodes.push_back(airline);
                }
                options.message += " using only the specified airlines";
            }
            options.message += "\n";
            printFlightsLists(g.getBestOption(source, searchFrom, dest, searchTo, maxAirlines, airlineCodes), options);
            break;
        }
        default: {
            printMainMenu();
        }
    }
}

/**
 * @brief Gets destinations from an airport in a maximum of stops
 * @param code Code of the source airport
 * @param stops Maximum of stops
 */
void Menu::getDestinations(std::string code, int stops) {
    std::cout << "Choose how to display destinations: \n"
              << "\t0 - Airports\n"
              << "\t1 - Cities\n"
              << "\t2 - Countries\n";
    int option;
    std::cin >> option;
    system("clear");
    printingOptions options;
    if (stops == 0) {
        options.message = "Destinations from the airport " + code + "\n";
    } else if (stops == INT32_MAX) {
        options.message = "All possible destinations from the airport " + code + "\n";
    } else {
        options.message = "Reachable destinations from the airport " + code + " in a maximum of " + std::to_string(stops) + " lay-overs\n";
    }
    switch (option) {
        case 0:
            printAirportsList(g.getReachableAirportsFrom(code, stops), options);
            break;
        case 1:
            printCitiesList(g.getReachableCitiesFrom(code, stops), options);
            break;
        case 2:
            printCountriesList(g.getReachableCountriesFrom(code, stops), options);
            break;
    }
}

/**
 * @brief Prints an airline list
 * @param airlines Airline list
 * @param options Printing options
 */
void Menu::printAirlinesList(std::vector<Airline *> airlines, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << airlines.size() << " airlines\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("Callsign", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortAirlinesList(airlines, options.sortOptions);

    // AIRLINES
    for (Airline *airline : airlines) {
        std::cout << "|" << center(airline->getCode(), ' ', CODE_WIDTH) << "|" << center(airline->getName(), ' ', NAME_WIDTH) << "|"
                  << center(airline->getCallsign(), ' ', DEFAULT_WIDTH) << "|" << center(airline->getCountry(), ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printAirlinesList(airlines, options);
        }
    }
}

/**
 * @brief Prints an airport list
 * @param airports Airport list
 * @param options Printing options
 */
void Menu::printAirportsList(std::vector<Airport*> airports, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << airports.size() << " airports\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|"
              << fill('-', OUTF_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("City", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|"
              << center("Latitude", ' ', NUMBER_WIDTH) << "|" << center("Longitude", ' ', NUMBER_WIDTH) << "|"
              << center("OutFlights", ' ', OUTF_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|"
              << fill('-', OUTF_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortAirportsList(airports, options.sortOptions);

    // AIRPORTS
    for (Airport *airport : airports) {
        std::cout << "|" << center(airport->getCode(), ' ', CODE_WIDTH) << "|" << center(airport->getName(), ' ', NAME_WIDTH) << "|"
                  << center(airport->getCity(), ' ', DEFAULT_WIDTH) << "|" << center(airport->getCountry(), ' ', DEFAULT_WIDTH) << "|"
                  << center(airport->getLatitude(), ' ', NUMBER_WIDTH) << "|" << center(airport->getLongitude(), ' ', NUMBER_WIDTH)<< "|"
                  << center(std::to_string(airport->getNFlightsOut()), ' ', OUTF_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|"
              << fill('-', OUTF_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printAirportsList(airports, options);
        }
    }
}

/**
 * @brief Prints a flight list
 * @param flights Flight list
 * @param options Printing options
 */
void Menu::printFlightsList(std::vector<Flight> flights, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << flights.size() << " flights\n";
    std::cout << "From " << flights.front().getSource()->getCode() << " To " << flights.back().getDest()->getCode() << "\n";

    // HEADERS: FROM and TO and AIRLINE
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "--" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "--" << fill('-', AIRLINE_WIDTH) << "|\n";

    std::cout << "|" << center("FROM", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|"
              << "|" << center("TO", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|"
              << "|" << center("AIRLINE", ' ', AIRLINE_WIDTH) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "|" << fill('-', AIRLINE_WIDTH) << "|\n";

    // SECONDARY HEADERS
    for (int i = 0; i < 2; i++) {
        std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("City", ' ', NAME_WIDTH) << "|"
                  << center("Country", ' ', NAME_WIDTH) << "|";
    }
    std::cout << "|" << center("Code", ' ', AIRLINE_WIDTH) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "|" << fill('-', AIRLINE_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortFlightsList(flights, options.sortOptions);

    // FLIGHTS
    for (Flight flight : flights) {
        std::cout << "|" << center(flight.getSource()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getSource()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getSource()->getCountry(), ' ', NAME_WIDTH) << "|"
                  << "|" << center(flight.getDest()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getDest()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getDest()->getCountry(), ' ', NAME_WIDTH) << "|"
                  << "|" << center(flight.getAirline()->getCode(), ' ', AIRLINE_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 4) * 2 + AIRLINE_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printFlightsList(flights, options);
        }
    }
}

/**
 * @brief Prints a city list
 * @param cities City list
 * @param options Printing options
 */
void Menu::printCitiesList(std::vector<std::pair<std::string, std::string>> cities, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << cities.size() << " cities\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', NAME_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|\n";
    std::cout << "|" << center("City", ' ', NAME_WIDTH) << "|" << center("Country", ' ', NAME_WIDTH) << "|\n";
    std::cout << "|" << fill('-', NAME_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortCitiesList(cities, options.sortOptions);

    // CITIES
    for (std::pair<std::string, std::string> city : cities) {
        std::cout << "|" << center(city.first, ' ', NAME_WIDTH) << "|" << center(city.second, ' ', NAME_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', NAME_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printCitiesList(cities, options);
        }
    }
}

/**
 * @brief Prints a country list
 * @param countries Country list
 * @param options Printing options
 */
void Menu::printCountriesList(std::vector<std::string> countries, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << countries.size() << " countries\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortCountriesList(countries, options.sortOptions);

    // COUNTRIES
    for (std::string country : countries) {
        std::cout << "|" << center(country, ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printCountriesList(countries, options);
        }
    }
}

/**
 * @brief Prints a source-destination pair of airports list
 * @param sourceDestPairs Source-destination pair of airports list
 * @param options Printing options
 */
void Menu::printSourceDestList(std::vector<std::pair<Airport *, Airport *>> sourceDestPairs, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << sourceDestPairs.size() << " source-destination pairs\n";
    std::cout << "\n";

    // HEADERS: FROM and TO and AIRLINE
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "--" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|\n";

    std::cout << "|" << center("FROM", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|"
              << "|" << center("TO", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "\n";

    // SECONDARY HEADERS
    for (int i = 0; i < 2; i++) {
        std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("City", ' ', NAME_WIDTH) << "|"
                  << center("Country", ' ', NAME_WIDTH) << "|";
    }
    std::cout << "\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "\n";

    // FLIGHTS
    for (auto sourceDest : sourceDestPairs) {
        std::cout << "|" << center(sourceDest.first->getCode(), ' ', CODE_WIDTH) << "|" << center(sourceDest.first->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(sourceDest.first->getCountry(), ' ', NAME_WIDTH) << "|"
                  << "|" << center(sourceDest.second->getCode(), ' ', CODE_WIDTH) << "|" << center(sourceDest.second->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(sourceDest.second->getCountry(), ' ', NAME_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 4) * 2 - 2) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        getInput();
    }
}

/**
 * @brief Prints a set of flight lists
 * @param flightsLists Flight lists
 * @param options Printing options
 */
void Menu::printFlightsLists(std::vector<std::vector<Flight>> flightsLists, printingOptions options) {
    system("clear");
    options.message +=  "There are " + std::to_string(flightsLists.size()) + " options\n\n";
    std::cout << "There are " << std::to_string(flightsLists.size()) << " options\n";
    if (flightsLists.empty()) {
        std::cout << "\n\n";
        endDisplayMenu();
        getInput();
        return;
    }
    std::cout << "Do you wish to display them? (y/n)";
    std::string option;
    std::cin >> option;
    options.sort = false;
    options.showSortingOptions = false;
    if (option == "y") {
        options.showEndMenu = false;
        options.getInput = false;
        for (int i = 0; i < flightsLists.size(); i++) {
            if (i == flightsLists.size() - 1) {
                options.showEndMenu = true;
                options.getInput = true;
            }
            printFlightsList(flightsLists[i], options);
            if (i == 0) {
                options.printMessage = false;
                options.clear = false;
            }
        }
    } else {
        endDisplayMenu();
        getInput();
    }
}


/**
 * @brief Returns a string with c repeated width times.
 * @param c Character to fill with
 * @param width Width of the string
 * @return String with length width filled with c
 */
std::string Menu::fill(char c, int width) {
    std::ostringstream oss;
    oss << std::setw(width) << std::setfill(c) << "";
    return oss.str();
}

/**
 * @brief Return a string of length width with str centered and surrounded by sep.
 * @param str
 * @param sep
 * @param width
 * @return String of length width with str centered and surrounded by sep
 */
std::string Menu::center(const std::string &str, char sep, int width) {
    std::ostringstream oss;
    std::string str2 = str;
    if (str.length() > width) {
        str2 = str.substr(0, width);
    }
    int space = (width - str2.length()) / 2;
    std::cout << std::setw(space) << std::setfill(sep) << "" << str2 << std::setw(width - str2.length() - space) << std::setfill(sep) << "";
    return oss.str();
}



void Menu::printBackToMenu() {
    std::cout << "Press 'm' to go back to the main menu.\n";
}

void Menu::printExit() {
    std::cout << "Press 'q' to quit.\n";
}

/**
 * @brief Receives input from the user.
 * @return
 */
char Menu::getInput() {
    char input;
    std::cin >> input;
    if (input == 'm') {
        printMainMenu();
    }
    return input;
}

/**
 * @brief Prints default menu after displaying anything that allows to go back to the main menu or exit the program.
 */
void Menu::endDisplayMenu() {
    printBackToMenu();
    printExit();
}
