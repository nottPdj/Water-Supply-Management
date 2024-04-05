#include "ServicePoint.h"

/**
 * @brief Service Point Constructor
 */
ServicePoint::ServicePoint() {}

/**
 *@brief Adds a pipe to a Service Point
 * @param pipe
 */
void ServicePoint::addPipe(Pipe * pipe) {
    adj.push_back(pipe);
}

/**
 * @brief Add a incoming pipe to a Service Point
 * @param pipe
 */
void ServicePoint::addIncomingPipe(Pipe * pipe) {
    incoming.push_back(pipe);
}

/**
 * @brief Removes a incoming pipe from a Service Point
 * @param pipe
 * @details Time Complexity O(n) n = number of incoming pipes
 */
void ServicePoint::removeIncomingPipe(Pipe * pipe) {
    auto it = incoming.begin();
    while (it != incoming.end()) {
        if ((*it) == pipe) {
            incoming.erase(it);
            break;
        } else {
            it++;
        }
    }
}

/**
 * @brief Removes an outgoing Pipe
 * @param pipe
 * @details Time Complexity O(n) n = number of outgoing pipes
 */
void ServicePoint::removeOutgoingPipe(Pipe * pipe) {
    auto it = adj.begin();
    while (it != adj.end()) {
        if ((*it) == pipe) {
            adj.erase(it);
            break;
        } else {
            it++;
        }
    }
}

/**
 * @brief Gets the adjacent Pipes
 * @return adj
 */
std::vector<Pipe *> ServicePoint::getAdj() const {
    return this->adj;
}

/**
 * @brief Checks if the Service Point is visited
 * @return visited
 */
bool ServicePoint::isVisited() const {
    return this->visited;
}

/**
 * @brief Gets the incoming Pipes
 * @return incoming
 */
std::vector<Pipe *> ServicePoint::getIncoming() const {
    return this->incoming;
}

/**
 * @brief Gets the path to the ServicePoint
 * @return path
 */
Pipe * ServicePoint::getPath() const {
    return this->path;
}

/**
 * @brief Sets ServicePoint as visited or not
 * @param visited
 */
void ServicePoint::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Sets the path to the ServicePoint
 * @param path
 */
void ServicePoint::setPath(Pipe *path) {
    this->path=path;
}
/**
 * @brief Sets the ServicePoint to operational or not
 * @param b
 */
void ServicePoint::setOperational(bool b) {
    operational=b;
}

/**
 * @brief Checks if the ServicePoint is operational
 * @return operational
 */
bool ServicePoint::isOperational() const {
    return operational;
}
