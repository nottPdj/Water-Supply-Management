//
// Created by pedro on 17-03-2024.
//

#ifndef PROJECT1_SERVICEPOINT_H
#define PROJECT1_SERVICEPOINT_H


#include <vector>
#include <string>

class ServicePoint {
public:
    ServicePoint(std::string in);
    bool operator<(ServicePoint<T> & ServicePoint) const; // // required by MutablePriorityQueue

    std::string getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(ServicePoint<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<ServicePoint>;
protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};


#endif //PROJECT1_SERVICEPOINT_H
