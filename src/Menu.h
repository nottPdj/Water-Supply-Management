#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

#include <string>
#include <vector>
#include "Management.h"


/**
 * @brief Menu auxiliary struct storing the printing options for a printing function.
 */
struct printingOptions {
    std::string message;
    std::string metrics;
    bool clear = true;
    bool printMessage = true;
    bool printTotal = true;
    bool printMetrics = false;
    bool showEndMenu = true;
};

/**
 * @brief Menu is used to create an interface between the user and the program.
 * Uses the console to receive and output inputs. There are some functionalities available only for Ubuntu.
 * */
class Menu {
private:
    /**
     * @brief Graph containing all the watter supply network information that is being managed.
     */
    Graph *g;
    /**
     * @brief Management extracts information from the graph containing the network and uses it to compute algorithms
     * that are needed to satisfy the user requests.
     */
    Management m;

    /**
     * @brief Contains the names of the datasets available.
     */
    std::string datasets[2] = {"Small", "Large"};
    int curDataset = 0;

    /**
     * @brief Path of the output file
     */
    std::string outputFile = "../data/output.txt";

    // Table column widths
    const static int MENU_WIDTH = 75;
    const static int CODE_WIDTH = 10;
    const static int FLOW_WIDTH = 10;
    const static int DEFICIT_WIDTH = 20;

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

    // Output file
    void clearOutputFile();

    // Choosing and selecting input
    ServicePoint * chooseReservoirInput();
    ServicePoint * chooseCityInput();
    ServicePoint * chooseStationInput();
    Pipe * choosePipeInput();

    // Auxiliary formatting functions
    std::string fill(char c, int width);
    std::string center(const std::string &str, char sep, int width);

    // Printing
    void printFlowPerCity(std::unordered_map<std::string,int> flowCities, printingOptions options);
    void printFlowDeficitPerCity(std::unordered_map<std::string,int> deficitCities, printingOptions options);
    void printCrucialPipes(std::vector<std::pair<Pipe *, flowDiff>> crucialPipes, printingOptions options);
    void printCitiesAffected(std::vector<std::pair<std::string, flowDiff>> citiesAffected, printingOptions options);
};


#endif //PROJECT1_MENU_H
