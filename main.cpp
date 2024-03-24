#include "src/Graph.h"
#include "src/Menu.h"
#include "src/Auxiliar.h"

int main() {
    Graph *g = new Graph();
    Auxiliar::readReservoir(g);
    Auxiliar::readStations(g);
    Auxiliar::readCities(g);
    Auxiliar::readPipes(g);
    Menu menu = Menu(g);
    menu.run();
    return 0;
}