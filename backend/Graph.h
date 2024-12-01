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
    void addEdge(Channel& a, Channel& b, int weight);
    bool hasEdge(Channel a, Channel b);
    vector<pair<Channel, int>> getNeighbors(Channel a);

    void addChannel(const Channel &channel);
};


#endif //PROJECT3_GRAPH_H
