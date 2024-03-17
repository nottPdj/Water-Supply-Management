#include "src/Graph.h"
#include "src/Menu.h"
#include "src/Auxiliar.h"

int main() {
    Graph g=Graph();
    Auxiliar::readAirports(g);
    Auxiliar::readAirlines(g);
    Auxiliar::readFlights(g);
    Menu menu = Menu(g);
    menu.run();
    return 0;
}