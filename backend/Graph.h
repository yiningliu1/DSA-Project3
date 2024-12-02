#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <iostream>
#include <vector>
#include "Channel.h"
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<pair<Channel, int>>> adjList;

public:
    Graph();
    void addEdge(Channel& a, Channel& b, int weight);
    bool hasEdge(Channel a, Channel b);
    vector<pair<Channel, int>> getNeighbors(Channel a);

    void addChannel(const Channel &channel);
};


#endif //PROJECT3_GRAPH_H
