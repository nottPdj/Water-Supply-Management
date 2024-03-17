#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

#include <string>
#include <vector>
#include "Graph.h"

/**
 * @brief Terminal auxiliary struct storing the sorting options of a table.
 */
struct sortingOptions {
    /**
     * Column, currently displaying, to order by
     */
    int orderBy = 0;
    bool ascending = true;
};

/**
 * @brief Terminal auxiliary struct storing the printing options for a printing function.
 */
struct printingOptions {
    sortingOptions sortOptions;
    std::string message;
    bool clear = true;
    bool printMessage = true;
    bool printCountMessage = true;
    bool sort = true;
    bool showSortingOptions = true;
    bool showEndMenu = true;
    bool getInput = true;
};

/**
 * @brief Terminal is used to create an interface between the user and the program.
 * Uses the console to receive and output inputs. There are some functionalities available only for Ubuntu.
 * */
class Menu {
private:
    /**
     * @brief Graph containing all the air travelling information that is being managed
     */
    Graph g;

    // Table column widths
    const static int MENU_WIDTH = 75;
    const static int CODE_WIDTH = 5;
    const static int OUTF_WIDTH = 13;
    const static int NAME_WIDTH = 43;
    const static int DEFAULT_WIDTH = 35;
    const static int NUMBER_WIDTH = 20;
    const static int AIRLINE_WIDTH = 9;

public:
    Terminal(const Graph &g);
    void run();

private:
    // Wait for inputs
    void waitMenu();
    char getInput();
    void getSortingOptions(sortingOptions &sortOptions);

    // Print menus
    void printMainMenu();
    void endDisplayMenu();
    void printBackToMenu();
    void printSortingOptions();
    void printExit();

    // Auxiliary formatting functions
    std::string fill(char c, int width);
    std::string center(const std::string &str, char sep, int width);

    // Auxiliary
    void getDestinations(std::string code, int stops = 0);

    // Printing
    void printFlightsLists(std::vector<std::vector<Flight>> flightsLists, printingOptions options);
    void printAirlinesList(std::vector<Airline *> airlines, printingOptions options);
    void printAirportsList(std::vector<Airport*> airports, printingOptions options);
    void printFlightsList(std::vector<Flight> flights, printingOptions options);
    void printCitiesList(std::vector<std::pair<std::string, std::string>> cities, printingOptions options);
    void printCountriesList(std::vector<std::string> countries, printingOptions options);
    void printSourceDestList(std::vector<std::pair<Airport *, Airport *>> sourceDestPairs, printingOptions options);

    // Sorting lists
    void sortAirportsList(std::vector<Airport *> &airports, sortingOptions sortOptions);
    void sortAirlinesList(std::vector<Airline *> &airlines, sortingOptions sortOptions);
    void sortFlightsList(std::vector<Flight> &flights, sortingOptions sortOptions);
    void sortCitiesList(std::vector<std::pair<std::string, std::string>> &cities, sortingOptions sortOptions);
    void sortCountriesList(std::vector<std::string> &countries, sortingOptions sortOptions);

    // Auxiliary sorting functions
    static bool byCity(std::pair<std::string, std::string> p1, std::pair<std::string, std::string> p2);
    static bool byCountry(std::pair<std::string, std::string> p1, std::pair<std::string, std::string> p2);
};


#endif //PROJECT1_MENU_H
