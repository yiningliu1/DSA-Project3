#include "Graph.h"
#include <unordered_map>
using namespace std;

void Graph::addEdge(Channel& a, Channel& b, int weight) {

    pair<Channel, int> p = make_pair(b, weight);
    adjList[a.id].push_back(p);
    p.first = a;
    adjList[b.id].push_back(p);
}

bool Graph::hasEdge(Channel a, Channel b) {
    vector<pair<Channel, int>> neighbors = adjList[a.id];
    for (auto neighbor : neighbors) {
        if (neighbor.first.id == b.id) {
            return true;
        }
    }
    return false;
}

vector<pair<Channel, int>> Graph::getNeighbors(Channel a) {
    return adjList[a.id];
}