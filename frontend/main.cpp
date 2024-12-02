#include "Channel.h"
#include "Graph.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void insertVertices(vector<Channel> channels) {
    rand();
}

vector<Channel> readChannels() {
    vector<Channel> channels;
    ifstream file("../channels.csv");
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cat, cat_name, id, country, followers, picURL, profURL, title, numVids;

        getline(ss, cat, ',');
        getline(ss, cat_name, ',');
        getline(ss, id, ',');
        getline(ss, country, ',');
        getline(ss, followers, ',');
        getline(ss, picURL, ',');
        getline(ss, profURL, ',');
        getline(ss, title, ',');
        getline(ss, numVids, ',');
        // int i, string n, string cntry, int cat, string pic, string prof, int subs
        Channel newChan(stoi(id), title, country, stoi(cat), picURL, profURL, stoi(followers));
        channels.push_back(newChan);
    }

    file.close();
    return channels;
}

int calculateWeight(Channel& a, Channel& b){
    int max = 70;
    int categoryWeight = (a.category == b.category) ? 30 : 0;
    int countryWeight = (a.country == b.country) ? 20 : 0;

    int subDiff = (a.subscribers - b.subscribers);
    int maxSub = std::max(a.subscribers, b.subscribers);
    int subWeight = 20 * (1 - (subDiff / maxSub));

    int Weight = max - (categoryWeight + countryWeight + subWeight);
    return Weight;
}

void RandomizeConnections(){

}



int main() {
    // read in all the channels
    vector<Channel> channels = readChannels();
    cout << channels.size() << endl;
    cout << channels[45643].id << " " << channels[45643].name << " " << channels[45643].category << " " << channels[45643].country << " " << channels[45643].subscribers << endl;
    srand(time(0));
    return 0;
}