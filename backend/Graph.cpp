#include "Graph.h"
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void Graph::addEdge(Channel& a, Channel& b, int weight) {
    adjList[a.name].push_back(make_pair(b, weight));
    adjList[b.name].push_back(make_pair(a, weight));
}

vector<pair<Channel, int>> Graph::getNeighbors(Channel a) {
    return adjList[a.name];
}

vector<pair<string, int>> Graph::Dijkstra(Channel source) {
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
        if (counter++ < 6 && currentDist != 0) result.push_back({currentName, currentDist});
        pq.pop();
        // Relax old distance
        if (currentDist > distances[currentName]) {
            continue;
        }
        for (auto it = adjList[currentName].begin(); it != adjList[currentName].end(); ++it) {
            Channel neighborChannel = it->first;
            int weight = it->second;

            int newDistance = currentDist + weight;

            // Relax edge
            if (newDistance < distances[neighborChannel.name]) {
                distances[neighborChannel.name] = newDistance;
                pq.push({newDistance, neighborChannel.name});
            }
        }
    }
    return result;
}

vector<pair<string, int>> Graph::BellmanFord(Channel source) {
    cout << "test" << endl;
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
    for (int i = 0; i < 5 && !pq.empty(); i++) {
        auto [dist, node] = pq.top();
        pq.pop();
        result.push_back({node, dist});
    }
    return result;
}