#ifndef PROJECT1_AUXILIAR_H
#define PROJECT1_AUXILIAR_H
#include "Graph.h"

/**
 * @brief Auxiliary class to read files
 */
class Auxiliar {
public:
    static void readDataset(Graph *g, int dataset = 0);
    static void readReservoir(Graph *g, int dataset);
    static void readStations(Graph *g, int dataset);
    static void readCities(Graph *g, int dataset);
    static void readPipes(Graph *g, int dataset);
};

#endif //PROJECT1_AUXILIAR_H
