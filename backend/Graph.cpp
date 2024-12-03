#include "Graph.h"

void Graph::addEdge(Channel& a, Channel& b, int weight) {
    adjList[a.id].push_back(make_pair(b, weight));
    adjList[b.id].push_back(make_pair(a, weight));
}

vector<pair<Channel, int>> Graph::getNeighbors(Channel a) {
    return adjList[a.id];
}

vector<pair<int, int>> Graph::Dijkstra(Channel source) {
    unordered_map<int, int> distances;
    unordered_map<int, int> previous;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        int key = it->first;
        distances[key] = numeric_limits<int>::max(); // Set distance to infinity
        previous[key] = -1; // Initialize previous channel to "-1"
    }
    distances[source.id] = 0;
    pq.push({0, source.id});

    while (!pq.empty()) {
        auto [currentDist, currentId] = pq.top();
        pq.pop();

        //relax old dist
        if (currentDist > distances[currentId]) {
            continue;
        }

        for (auto it = adjList[currentId].begin(); it != adjList[currentId].end(); ++it) {
            Channel neighborChannel = it->first;
            int weight = it->second;

            int newDistance = currentDist + weight;

            // Relax edge
            if (newDistance < distances[neighborChannel.id]) {
                distances[neighborChannel.id] = newDistance;
                previous[neighborChannel.id] = currentId;
                pq.push({newDistance, neighborChannel.id});
            }
        }
    }
    vector<pair<int, int>> result;
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        result.push_back({it->first, it->second});
    }
    return result;
}

vector<pair<int, int>> Graph::BellmanFord(Channel source){
    unordered_map<int, int> distances;
    unordered_map<int, int> previous;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        int key = it->first;
        distances[key] = numeric_limits<int>::max(); // Set distance to infinity
        previous[key] = -1; // Initialize previous channel to "-1"
    }
    distances[source.id] = 0;
    //relax V times to check for negative weight cycle
    for (int i = 0; i < adjList.size(); ++i) {
        for (auto [u, neighbors] : adjList) {
                for (auto& neighbor : neighbors) {
                    int v = neighbor.first.id;
                    int weight = neighbor.second;  
                    // relax
                    if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        previous[v] = u;
                    }
                }
            }
        if (i == adjList.size() - 1) {
            for (auto& [u, neighbors] : adjList) {
                for (auto& neighbor : neighbors) {
                    int v = neighbor.first.id;
                    int weight = neighbor.second;

                    // if Vth relax then there is a negative weight cycle
                    if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        return {}; 
                    }
                }
            }
        }
    }
    vector<pair<int, int>> result;
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        result.push_back({it->first, it->second});
    }
    return result;
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
    // Extract the top 5 shortest distances
    for (int i = 0; i < 5 && !pq.empty(); i++) {
        auto [dist, node] = pq.top();
        pq.pop();
        result.push_back({node, dist});
    }
    return result;
}