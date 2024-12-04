#include "Graph.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <vector>
#include <string>
using namespace std;

// adds edge between two channels
void Graph::addEdge(Channel& a, Channel& b, int weight) {
    adjList[a.name].push_back(make_pair(b, weight));
    adjList[b.name].push_back(make_pair(a, weight));
}

// performs Dijkstra's algorithm on all vertices, only returns 5 closest
vector<pair<string, int>> Graph::Dijkstra(Channel source) {
    unordered_set<string> visited;
    unordered_map<string, int> distances;
    int counter = 0;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    vector<pair<string, int>> result;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        string key = it->first;
        distances[key] = numeric_limits<int>::max(); // Set distance to infinity
    }
    distances[source.name] = 0;
    pq.push({0, source.name});

    while (!pq.empty()) {
        auto [currentDist, currentName] = pq.top();
        if (counter++ < 6 && currentDist != 0) { // only save 5 shortest distances to result
            result.push_back({currentName, currentDist});
            visited.insert(currentName);
        }
        pq.pop();
        if (visited.find(currentName) != visited.end()) {
            continue;
        }
        // Relax old distance
        if (currentDist > distances[currentName]) {
            continue;
        }
        for (auto it = adjList[currentName].begin(); it != adjList[currentName].end(); ++it) {
            Channel neighborChannel = it->first;
            int weight = it->second;
            int newDistance = currentDist + weight;
            // Relax edge
            if (newDistance < distances[neighborChannel.name] && visited.find(neighborChannel.name) == visited.end()) {
                distances[neighborChannel.name] = newDistance;
                pq.push({newDistance, neighborChannel.name});
            }
        }
    }
    return result;
}

// performs Bellman Ford on all vertices, only returns 5 closest
vector<pair<string, int>> Graph::BellmanFord(Channel source) {
    unordered_map<string, int> distances;
    vector<pair<string, int>> result;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        string key = it->first;
        distances[key] = numeric_limits<int>::max(); // Set distance to infinity
    }
    distances[source.name] = 0;
    int i = 0;

    vector<tuple<string, string, int>> edges;
    for (const auto& [u, neighbors] : adjList) {
        for (const auto& neighbor : neighbors) {
            edges.push_back({u, neighbor.first.name, neighbor.second});
        }
    }

    bool relaxed = false;
    // Relax V times to check for negative weight cycle
    for (int i = 0; i < adjList.size(); i++) {
        relaxed = false;
        for (const auto& [u, v, weight] : edges) {
            // Relax the edge
            if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                relaxed = true;
            }
        }
        if (!relaxed) {
            break;
        }

        // On the V-th iteration there's a negative weight cycle if relax
        if (i == adjList.size() - 1 && relaxed) {
            return {};
        }
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    for (const auto& [node, distance] : distances) {
        if (distance != numeric_limits<int>::max()) {
            pq.push({distance, node});
        }
    }

    // Extract the top 5 shortest distances
    pq.pop();
    for (int i = 0; i < 5 && !pq.empty(); i++) {
        auto [dist, node] = pq.top();
        pq.pop();
        result.push_back({node, dist});
    }
    return result;
}