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
    unordered_map<int, vector<pair<Channel, int>>> adjList;

public:
    void addEdge(Channel& a, Channel& b, int weight);
    vector<pair<Channel, int>> getNeighbors(Channel a);
    vector<pair<int, int>> Dijkstra(Channel a);
    vector<pair<int, int>> BellmanFord(Channel source);
};


#endif //PROJECT3_GRAPH_H
