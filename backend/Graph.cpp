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

vector<pair<string, int>> Graph::Dijkstra(Channel source) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // Initialize distances to infinity and prev to -1
    for (auto& bucket : adjList.getBuckets()) {
        hashObj* current = bucket;
        while (current) {
            distances[current->key] = numeric_limits<int>::max();
            previous[current->key] = '-1';
            current = current->next;
        }
    }

    distances[source.id] = 0;
    pq.push({0, source.id}); // push source to priority queue

    while (!pq.empty()) {
        // smallest distance
        auto [currentDist, currentId] = pq.top();
        pq.pop();

        // relaxing old distances
        if (currentDist > distances[currentId]) {
            continue;
        }
        
        for (const auto& neighbor : adjList.retrieve(currentId)) {
            Channel neighborChannel = neighbor.first; 
            int weight = neighbor.second;           

            int newDistance = currentDist + weight;

            // Relax
            if (newDistance < distances[neighborChannel.id]) {
                distances[neighborChannel.id] = newDistance;  
                previous[neighborChannel.id] = currentId; 
                pq.push({newDistance, neighborChannel.id});  // Push to pq
            }
        }
    }

    vector<pair<string, int>> result;
    for (auto& [key, dist] : distances) {
        result.push_back({key, dist});
    }

    //  vector<pair<Channel, int>> result;
    // for (auto& bucket : adjList.getBuckets()) {
    //     hashObj* current = bucket;
    //     while (current) {
    //             for (auto& [channel, weight] : current->val) {
    //             if (distances.count(channel.id)) {
    //                 result.push_back({channel, distances[channel.id]});
    //             }
    //         }
    //         current = current->next;
    //     }
    // }

    return result;
}