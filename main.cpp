#include "src/Graph.h"
#include "src/Menu.h"
#include "src/Auxiliar.h"

int main() {
    Graph *g = new Graph();
    Auxiliar::readDataset(g);
    Menu menu = Menu(g);
    menu.run();
    return 0;
}