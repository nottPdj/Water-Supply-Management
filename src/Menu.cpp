#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "Menu.h"
#include "Auxiliar.h"


/**
 * @brief Constructor of the Menu class. Stores the graph containing all the watter supply network information
 * in the private field and creates and stores a management class that is responsible for managing this graph.
 * @param g Graph containing all the watter supply network information
 */
Menu::Menu(Graph *g) : m(Management(g)), g(g)  {}

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
              << "\t\t0 - a city" << "\n"
              << "\t\t1 - each city" << "\n"
              << "\t2 - Check if current network configuration meets the water needs of all customers" << "\n"
              << "\t3 - Balance the load across the network" << "\n\n"
              << "Reliability and Sensitivity to Failures" << "\n"
              << "\t4 - Water Reservoir unavailable" << "\n"
              << "\t5 - Cities affected by a pumping station failure" << "\n"
              << "\t6 - Crucial pipelines to a city" << "\n"
              << "\t7 - Cities affected by pipeline rupture" << "\n\n"
              << "8 - Choose dataset (current: " << datasets[curDataset] << ")" << "\n\n";

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
        // Maximum amount of water that can reach a city
        case 0: {
            ServicePoint * city = chooseCityInput();
            std::pair<std::string, int> flow = m.getMaxFlowCity(city);
            std::unordered_map<std::string,int> flowCities;
            flowCities.insert(flow);
            options.message = "Maximum amount of water that can reach city " + city->getCode() + "\n\n";
            options.printTotal = false;
            printFlowPerCity(flowCities, options);
            break;
        }
        // Maximum amount of water that can reach each city
        case 1: {
            std::unordered_map<std::string,int> flow = m.getMaxFlow();
            options.message = "Maximum amount of water that can reach city each city\n";
            printFlowPerCity(flow, options);
            break;
        }
        // Check if current network configuration meets the water needs of all customers
        case 2: {
            std::unordered_map<std::string,int> deficitCities = m.getFlowDeficit();
            printFlowDeficitPerCity(deficitCities, options);
            break;
        }
        // Balance the load across the network
        case 3: {

            break;
        }
        // Water Reservoir unavailable
        case 4: {
            ServicePoint * reservoir = chooseReservoirInput();
            std::vector<std::pair<std::string, flowDiff>> citiesAffectedByReservoirFail = m.getCitiesAffectedByReservoirFail(reservoir);
            options.message = "Cities affected by reservoir " + reservoir->getCode() + "\n\n";
            printCitiesAffected(citiesAffectedByReservoirFail, options);
            break;
        }
        // Cities affected by a pumping station failure
        case 5: {
            ServicePoint * station = chooseStationInput();
            std::vector<std::pair<std::string, flowDiff>> citiesAffectedByStationFail = m.getCitiesAffectedByStationFail(station);
            options.message = "Cities affected if station " + station->getCode() + " fails\n\n";
            printCitiesAffected(citiesAffectedByStationFail, options);
            break;
        }
        // Crucial pipelines to a city
        case 6: {
            ServicePoint * city = chooseCityInput();
            std::vector<std::pair<Pipe *, flowDiff>> crucialPipesToCity = m.getCrucialPipesToCity(city);
            options.message = "Crucial pipelines to city " + city->getCode() + "\n\n";
            options.printTotal = false;
            printCrucialPipes(crucialPipesToCity, options);
            break;
        }
        // Cities affected by pipeline rupture
        case 7: {
            Pipe * pipe = choosePipeInput();
            std::vector<std::pair<std::string, flowDiff>> citiesAffectedByPipeRupture = m.getCitiesAffectedByPipeRupture(pipe);
            options.message = "Cities affected by pipeline rupture (" + pipe->getOrig()->getCode() + ", " + pipe->getDest()->getCode() + ")\n\n";
            printCitiesAffected(citiesAffectedByPipeRupture, options);
            break;
        }
        // Choose dataset
        case 8: {
            std::cout << "Choose what dataset to use:\n";
            std::cout << "\t0 - Small Dataset\n";
            std::cout << "\t1 - Large Dataset\n";
            std::cin >> curDataset;
            g = new Graph();
            Auxiliar::readDataset(g, curDataset);
            m = Management(g);
        }
        default: {
            printMainMenu();
        }
    }
}


/**
 * @brief Choose how the reservoir is input and returns the reservoir.
 * @return Service Point pointer that was chosen.
 */
ServicePoint * Menu::chooseReservoirInput() {
    system("clear");
    std::cout << "Choose reservoir by:\n";
    std::cout << "\t0 - code\n";
    std::cout << "\t1 - name\n";
    int option;
    std::cin >> option;
    system("clear");
    if (option == 1) {
        std::string name;
        std::cout << "Enter the reservoir name: ";
        std::getline(std::cin >> std::ws, name);
        return g->getReservoirByName(name);
    }
    else {
        std::string code;
        std::cout << "Enter the reservoir code: ";
        std::cin >> code;
        return g->findServicePoint(code);
    }
}

/**
 * @brief Choose how the city is input and returns the city.
 * @return Service Point pointer that was chosen.
 */
ServicePoint * Menu::chooseCityInput() {
    system("clear");
    std::cout << "Choose city by:\n";
    std::cout << "\t0 - code\n";
    std::cout << "\t1 - name\n";
    int option;
    std::cin >> option;
    system("clear");
    if (option == 1) {
        std::string name;
        std::cout << "Enter the city name: ";
        std::getline(std::cin >> std::ws, name);
        return g->getCityByName(name);
    }
    else {
        std::string code;
        std::cout << "Enter the city code: ";
        std::cin >> code;
        return g->findServicePoint(code);
    }
}

/**
 * @brief Receives the station input and returns the station.
 * @return Service Point pointer that was chosen.
 */
ServicePoint * Menu::chooseStationInput() {
    system("clear");
    std::string code;
    std::cout << "Enter the station code: ";
    std::cin >> code;
    return g->findServicePoint(code);
}

/**
 * @brief Receives the pipe's source and target service points inputs by code and returns the station.
 * @return Service Point pointer that was chosen.
 */
Pipe * Menu::choosePipeInput() {
    system("clear");
    std::string orig, dest;
    std::cout << "Enter the code of the source service point: ";
    std::cin >> orig;
    std::cout << "Enter the code of the target service point: ";
    std::cin >> dest;
    return g->getPipeByEnds(orig, dest);
}


/**
 * @brief Prints in a tabular form the code of the city and the respective flow, as well as the total in the end
 * @param flowCities Hashmap that contains the flow per city
 * @param options Printing options
 */
void Menu::printFlowPerCity(std::unordered_map<std::string,int> flowCities, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Flow", ' ', FLOW_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|\n";

    // CITIES AND FLOWS
    int total = 0;
    for (auto it = flowCities.begin(); it != flowCities.end(); it++) {
        total += it->second;
        std::cout << "|" << center(it->first, ' ', CODE_WIDTH) << "|" << center(std::to_string(it->second), ' ', FLOW_WIDTH) << "|\n";
    }
    if (options.printTotal)
        std::cout << "|" << center("TOTAL", ' ', CODE_WIDTH) << "|" << center(std::to_string(total), ' ', FLOW_WIDTH) << "|\n";


    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    getInput();
}

/**
 * @brief Prints in a tabular form the code of the city and the respective flow deficit, as well as the total in the end
 * @param deficitCities Hashmap that contains the flow deficit per city
 * @param options Printing options
 */
void Menu::printFlowDeficitPerCity(std::unordered_map<std::string,int> deficitCities, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        if (deficitCities.empty()) {
            options.message = "There exists a network configuration that meets the water needs of its customers.\n\n";
        } else {
            options.message = "These cities are not being delivered as much water as needed:\n\n";
        }
    std::cout << options.message;

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Flow Deficit", ' ', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    // CITIES AND FLOWS
    int total = 0;
    for (auto it = deficitCities.begin(); it != deficitCities.end(); it++) {
        total += it->second;
        std::cout << "|" << center(it->first, ' ', CODE_WIDTH) << "|" << center(std::to_string(it->second), ' ', DEFICIT_WIDTH) << "|\n";
    }
    if (options.printTotal)
        std::cout << "|" << center("TOTAL", ' ', CODE_WIDTH) << "|" << center(std::to_string(total), ' ', DEFICIT_WIDTH) << "|\n";


    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    getInput();
}

/**
 * @brief Prints in a tabular form the codes of the pipe's source and target service points, and the respective previous
 * and new flow, as well as the flow difference
 * @param crucialPipes Pipe and respective previous and new flow
 * @param options Printing options
 */
void Menu::printCrucialPipes(std::vector<std::pair<Pipe *, flowDiff>> crucialPipes, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << center("Source", ' ', CODE_WIDTH) << "|" << center("Target", ' ', CODE_WIDTH) << "|" << center("Old Flow", ' ', FLOW_WIDTH) << "|" << center("New Flow", ' ', FLOW_WIDTH) << "|" << center("Flow Difference", ' ', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    // CITIES AND FLOWS
    for (std::pair<Pipe *, flowDiff> pipeDiff : crucialPipes) {
        Pipe * pipe = pipeDiff.first;
        int oldFlow = pipeDiff.second.oldFlow;
        int newFlow = pipeDiff.second.newFlow;
        std::cout << "|" << center(pipe->getOrig()->getCode(), ' ', CODE_WIDTH) << "|" << center(pipe->getDest()->getCode(), ' ', CODE_WIDTH) << "|" << center(std::to_string(oldFlow), ' ', FLOW_WIDTH) << "|" << center(std::to_string(newFlow), ' ', FLOW_WIDTH) << "|" << center(std::to_string(newFlow - oldFlow), ' ', DEFICIT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    getInput();
}

/**
 * @brief Prints in a tabular form the code of the city, and the respective previous
 * and new flow, as well as the flow difference and the total in the end
 * @param citiesAffected Code of the city and respective previous and new flow
 * @param options Printing options
 */
void Menu::printCitiesAffected(std::vector<std::pair<std::string, flowDiff>> citiesAffected, printingOptions options) {
    if (options.clear)
        system("clear");
    if (options.printMessage)
        std::cout << options.message;

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Old Flow", ' ', FLOW_WIDTH) << "|" << center("New Flow", ' ', FLOW_WIDTH) << "|" << center("Flow Difference", ' ', DEFICIT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    // CITIES AND FLOWS
    int totalOld = 0;
    int totalNew = 0;
    for (std::pair<std::string, flowDiff> cityDiff : citiesAffected) {
        int oldFlow = cityDiff.second.oldFlow;
        int newFlow = cityDiff.second.newFlow;
        totalOld += oldFlow;
        totalNew += newFlow;
        std::cout << "|" << center(cityDiff.first, ' ', CODE_WIDTH) << "|" << center(std::to_string(oldFlow), ' ', FLOW_WIDTH) << "|" << center(std::to_string(newFlow), ' ', FLOW_WIDTH) << "|" << center(std::to_string(newFlow - oldFlow), ' ', DEFICIT_WIDTH) << "|\n";
    }
    if (options.printTotal)
        std::cout << "|" << center("TOTAL", ' ', CODE_WIDTH) << "|" << center(std::to_string(totalOld), ' ', FLOW_WIDTH) << "|" << center(std::to_string(totalNew), ' ', FLOW_WIDTH) << "|" << center(std::to_string(totalNew - totalOld), ' ', DEFICIT_WIDTH) << "|\n";

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    getInput();
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
