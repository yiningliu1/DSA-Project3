#include "Graph.h"

void Graph::addChannel(const Channel& channel) {
    pair<Channel, int> p = make_pair(channel, -1);
    adjList.insert(channel.id, p); // Initialize empty adjacency list
}

void Graph::addEdge(Channel& a, Channel& b, int weight) {
    pair<Channel, int> p = make_pair(b, weight);
    adjList.insert(a.id, p);
    p.first = a;
    adjList.insert(b.id, p);
}

bool Graph::hasEdge(Channel a, Channel b) {
    vector<pair<Channel, int>> neighbors = adjList.retrieve(a.id);

    for (auto neighbor : neighbors) {
        if (neighbor.first.id == b.id) {
            return true;
        }
    }
    return false;
}

vector<pair<Channel, int>> Graph::getNeighbors(Channel a) {
    return adjList.retrieve(a.id);
}
