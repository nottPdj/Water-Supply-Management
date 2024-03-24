#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

#include <string>
#include <vector>
#include "Management.h"


/**
 * @brief Terminal auxiliary struct storing the printing options for a printing function.
 */
struct printingOptions {
    std::string message;
    bool clear = true;
    bool printMessage = true;
    bool showEndMenu = true;
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
    Graph *g;
    Management m;

    // Table column widths
    const static int MENU_WIDTH = 75;
    const static int CODE_WIDTH = 10;
    const static int FLOW_WIDTH = 10;
    const static int OUTF_WIDTH = 13;
    const static int NAME_WIDTH = 43;
    const static int DEFAULT_WIDTH = 35;
    const static int NUMBER_WIDTH = 20;
    const static int AIRLINE_WIDTH = 9;

public:
    Menu(Graph *g);
    void run();

private:
    // Wait for inputs
    void waitMenu();
    char getInput();

    // Print menus
    void printMainMenu();
    void endDisplayMenu();
    void printBackToMenu();
    void printExit();

    ServicePoint * chooseCityInput();

    // Auxiliary formatting functions
    std::string fill(char c, int width);
    std::string center(const std::string &str, char sep, int width);

    // Printing
    void printFlowPerCity(std::vector<std::pair<std::string, int>> flowCities, printingOptions options);

};


#endif //PROJECT1_MENU_H
