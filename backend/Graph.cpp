#include "Graph.h"


void Graph::addEdge(Channel a, Channel b, int weight, bool directed = false) {
    Channel neighborB(b.id, b.name, b.country, b.category, b.pictureURL, b.profileURL, b.numVideos, weight);
    adjList.insert(a.id, neighborB);

    if (!directed) {
        Channel neighborA(a.id, a.name, a.country, a.category, a.pictureURL, a.profileURL, a.numVideos, weight);
        adjList.insert(b.id, neighborA);
    }
}

bool Graph::hasEdge(Channel a, Channel b) {
    vector<Channel> neighbors = adjList.retrieve(a.id);

    for (auto neighbor : neighbors) {
        if (neighbor.id == b.id) {
            return true;
        }
    }
    return false;
}

vector<Channel> Graph::getNeighbors(Channel a) {
    return adjList.retrieve(a.id);
}