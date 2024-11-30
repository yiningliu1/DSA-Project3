#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <iostream>
#include "HashMap.h"
using namespace std;

class Graph {
private:
    HashMap adjList;

public:
    Graph();
    void addEdge(Channel a, Channel b, int weight, bool directed = false);
    bool hasEdge(Channel a, Channel b);
    vector<Channel> getNeighbors(Channel a);
};


#endif //PROJECT3_GRAPH_H
