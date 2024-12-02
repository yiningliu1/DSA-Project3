#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <iostream>
#include "HashMap.h"
#include <queue>
#include <unordered_map>
#include <limits>
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
    vector<pair<string, int>> Dijkstra(Channel a);
};


#endif //PROJECT3_GRAPH_H
