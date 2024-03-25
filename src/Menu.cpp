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
Menu::Menu(Graph *g) : m(Management(g)), g(g)  {}

/**
 * @brief This method is called to start the interface.
 */
void Menu::run(){
    system("clear");
    //printChooseDataset();
    printMainMenu();
    system("clear");
}

// void Menu::printChooseDataset() {
//     std::cout << "Choose a dataset to load:" << std::endl;
//     //
// }


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
              << "\t3 - Balance the load across the network" << "\n"
              << "Reliability and Sensitivity to Failures" << "\n"
              << "\t4 - Water Reservoir unavailable" << "\n"
              << "\t5 - Pumping Station unavailable" << "\n"
              << "\t6 - Crucial pipelines" << "\n\n"
              << "\t7 - Choose dataset" << "\n\n";

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
        //
        case 0: {
            ServicePoint * city = chooseCityInput();
            std::pair<std::string, int> flow = m.getMaxFlowCity(city);
            std::vector<std::pair<std::string, int>> flowCities = {flow};
            printingOptions options;
            options.message = "Maximum amount of water that can reach city \n"; // TODO
            printFlowPerCity(flowCities, options);
            break;
        }
        case 1: {
            printingOptions options;
            std::vector<std::pair<std::string, int>> flow = m.getMaxFlow();
            printFlowPerCity(flow, options);
        }
        case 2: {
            printingOptions options;
            std::vector<std::pair<std::string, int>> deficitCities = m.getFlowDeficit();
            printFlowDeficitPerCity(deficitCities, options);
        }
        default: {
            printMainMenu();
        }
    }
}

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

void Menu::printFlowPerCity(std::vector<std::pair<std::string, int>> flowCities, printingOptions options) {
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
    for (std::pair<std::string, int> city : flowCities) {
        total += city.second;
        std::cout << "|" << center(city.first, ' ', CODE_WIDTH) << "|" << center(std::to_string(city.second), ' ', FLOW_WIDTH) << "|\n";
    }
    std::cout << "|" << center("TOTAL", ' ', CODE_WIDTH) << "|" << center(std::to_string(total), ' ', FLOW_WIDTH) << "|\n";


    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', FLOW_WIDTH) << "|\n";

    std::cout << "\n\n";
    if (options.showEndMenu)
        endDisplayMenu();
    getInput();
}

void Menu::printFlowDeficitPerCity(std::vector<std::pair<std::string, int>> deficitCities, printingOptions options) {
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
    for (std::pair<std::string, int> city : deficitCities) {
        total += city.second;
        std::cout << "|" << center(city.first, ' ', CODE_WIDTH) << "|" << center(std::to_string(city.second), ' ', DEFICIT_WIDTH) << "|\n";
    }
    std::cout << "|" << center("TOTAL", ' ', CODE_WIDTH) << "|" << center(std::to_string(total), ' ', DEFICIT_WIDTH) << "|\n";


    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFICIT_WIDTH) << "|\n";

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
