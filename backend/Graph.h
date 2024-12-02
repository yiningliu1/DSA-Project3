#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <iostream>
#include <queue>
#include "Channel.h"
#include <unordered_map>
#include <limits>
#include <vector>
using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<Channel, int>>> adjList;

public:
    Graph();
    void addEdge(Channel& a, Channel& b, int weight);
    bool hasEdge(Channel a, Channel b);
    vector<pair<Channel, int>> getNeighbors(Channel a);
    void addChannel(const Channel &channel);
    vector<pair<int, int>> Dijkstra(Channel a);
    vector<pair<int, int>> BellmanFord(Channel source);
};


#endif //PROJECT3_GRAPH_H
