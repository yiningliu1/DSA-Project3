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

int Graph::calculateWeight(Channel& a, Channel& b){
    int categoryWeight = (a.category == b.category) ? 0 : 10000;
    int countryWeight = (a.country == b.country) ? 0 : 2500;

    int subDiff = abs(a.subscribers - b.subscribers);
    int maxSub = std::max(a.subscribers, b.subscribers);
    int subWeight =  2500 * ((double)subDiff / (double)maxSub);

    int weight = 1 + categoryWeight + countryWeight + subWeight;
    return weight;
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
        if (counter++ < 5 && currentDist != 0) result.push_back({currentName, currentDist});
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

unordered_map<string, int> Graph::BellmanFord(Channel source) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        string key = it->first;
        distances[key] = numeric_limits<int>::max(); // Set distance to infinity
        previous[key] = ""; // Initialize previous channel to empty string
    }
    distances[source.name] = 0;

    // Relax V times to check for negative weight cycle
        for (auto [u, neighbors] : adjList) {
            for (auto& neighbor : neighbors) {
                string v = neighbor.first.name;
                int weight = neighbor.second;

                // Relax
                if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                }
            }
        }

        if (i == adjList.size() - 1) {
            for (auto& [u, neighbors] : adjList) {
                for (auto& neighbor : neighbors) {
                    string v = neighbor.first.name;
                    int weight = neighbor.second;

                    // If Vth relax then there is a negative weight cycle
                    if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        return {};
                    }
                }
            }
        }

    return distances;
}