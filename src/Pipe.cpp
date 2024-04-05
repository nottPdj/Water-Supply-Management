#include "Pipe.h"

/**
 * @brief Pipe Constructor
 * @param orig
 * @param dest
 * @param capacity
 */
Pipe::Pipe(ServicePoint *orig, ServicePoint *dest, int capacity): orig(orig), dest(dest), capacity(capacity) {}

/**
 * @details Gets ServicePoint destination
 * @return dest
 */
ServicePoint * Pipe::getDest()  {
    return this->dest;
}

/**
 * @brief Gets Pipe capacity
 * @return capacity
 */
double Pipe::getCapacity() const {
    return this->capacity;
}

/**
 * @brief Gets origin Pipe
 * @return orig
 */
ServicePoint * Pipe::getOrig()  {
    return this->orig;
}

/**
 * @brief Gets the reversed Pipe
 * @return reverse
 */
Pipe *Pipe::getReverse() const {
    return this->reverse;
}

/**
 * @brief Checks if the pipe is visited
 * @return visited
 */
bool Pipe::isVisited() const {
    return this->visited;
}

/**
 * @brief Gets the flow of a Pipe
 * @return flow
 */
double Pipe::getFlow() const {
    return flow;
}

/**
 * @brief Sets the reverse Pipe
 * @param reverse
 */
void Pipe::setReverse(Pipe *reverse) {
    this->reverse = reverse;
}

/**
 * @brief Sets the flow of Pipe
 * @param flow
 */
void Pipe::setFlow(double flow) {
    this->flow = flow;
}

/**
 * @brief Sets the Pipe to operational or not
 * @param b
 */
void Pipe::setOperational(bool b) {
    operational=b;
}

/**
 * @brief Sets the Pipe to visited or not
 * @param visited
 */
void Pipe::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Checks if the Pipe is visited or not
 * @return operational
 */
bool Pipe::isOperational() const {
    return operational;
}




