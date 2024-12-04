#include "../backend/Channel.h"
#include "../backend/Graph.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

// function to read in all the channels
vector<Channel> readChannels(unordered_map<string, int>& chanMap) {
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

        Channel newChan(stoi(id), title, country, stoi(cat), picURL, profURL, stoi(followers));

        // save titles to a map that stores the indices
        chanMap[title] = channels.size();

        channels.push_back(newChan);
    }

    file.close();

    return channels;
}

// sets SFML text
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

// calculates the weight for an edge between two channels
int calculateWeight(Channel& a, Channel& b){
    int categoryWeight = 0;
    int countryWeight = 0;
    if (a.category != b.category)  categoryWeight = 10000;
    if (a.country != b.country)  countryWeight = 2500;

    int subDiff = abs(a.subscribers - b.subscribers);
    int maxSub = std::max(a.subscribers, b.subscribers);
    int subWeight =  2000 * ((double)subDiff / (double)maxSub);

    int weight = 1 + categoryWeight + countryWeight + subWeight;
    return weight;
}

// randomly creates edges between channels
void RandomizeConnections(Channel c1, const vector<Channel>& channels, Graph& graph) {
    unordered_set<int> connected;
    connected.insert(c1.id-1);
    int totalChannels = channels.size();
    for (int i = 0; i < 10; i++) { // selects 10 random channels for each channel
        int randChannel = rand() % totalChannels;
        if (connected.find(randChannel) != connected.end()) {
            i--;
            continue;
        }
        connected.insert(randChannel);
        Channel c2 = channels[randChannel];
        int weight = calculateWeight(c1, c2);
        graph.addEdge(c1, c2, weight);
    }
}

// calls randomizeConnections on every channel
void addEdges(const vector<Channel>& channels, Graph& graph) {
    srand(time(0));
    for (Channel c: channels) {
        RandomizeConnections(c, channels, graph);
    }
}

// calls Dijkstra and Bellman Ford search on specified channel and returns the 5 closest channels
vector<Channel> performSearch(const vector<Channel>& channels, unordered_map<string, int>& chanMap, Graph& graph, const string& name, int& dTime, int& bTime) {
    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> res = graph.Dijkstra(channels[chanMap[name]]);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    dTime = duration.count(); // time for Dijkstra execution in milliseconds

    start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> bf = graph.BellmanFord(channels[chanMap[name]]);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    bTime = duration.count(); // time for Bellman Ford execution in milliseconds

    vector<Channel> closest;
    for (auto i: res) {
        closest.push_back(channels[chanMap[i.first]]);
    }

    return closest;
}

int main() {
    // initialize variables
    int dTime = 0;
    int bTime = 0;
    vector<Channel> recs;
    Graph graph;
    unordered_map<string, int> inds;
    vector<Channel> channels = readChannels(inds);
    addEdges(channels, graph);

    // render first window and set text and background
    sf::RenderWindow window(sf::VideoMode(800, 800), "Youtube Recommender");
    sf::RenderWindow resultwindow;
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        cout << "error" << endl;
    }
    sf::Text text1;
    sf::Text text2;
    text1.setFont(font);
    text1.setString("Find Similar Youtube Channels");
    text1.setCharacterSize(30);
    text1.setFillColor(sf::Color::White);
    setText(text1, 400, 25);
    text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text2.setFont(font);
    text2.setString("Enter Channel name:");
    text2.setCharacterSize(20);
    text2.setFillColor(sf::Color::White);
    setText(text2, 400, 200);
    text2.setStyle(sf::Text::Bold);
    string playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::White);
    playerText.setStyle(sf::Text::Bold);

    while (window.isOpen()) { // event loop for first window
        setText(playerText, 400, 250);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) { // modify text displayed on screen
                if (isalpha(event.text.unicode) || isdigit(event.text.unicode) || isspace(event.text.unicode)) {
                    char a = event.text.unicode;
                    playerInput += a;
                }
                playerText.setString(playerInput + "|");
                if (event.text.unicode == 8 && playerInput.length() >= 1) {
                    playerInput.pop_back();
                    playerText.setString(playerInput + "|");
                }
                if (event.text.unicode == 13) { // after user presses enter
                    string chanName = playerInput.substr(0, playerInput.size()-1);
                    if (inds.find(chanName) == inds.end()) { // ensure channel exists
                        text2.setString("That channel does not exist. Please try something else:");
                        setText(text2, 400, 200);
                    } else { // open results window and perform search on channel
                        setText(text2, 400, 200);
                        window.close();
                        resultwindow.create(sf::VideoMode(800, 800), "Youtube Recommender");
                        recs = performSearch(channels, inds, graph, chanName, dTime, bTime);
                    }
                }
            }
        }

        window.clear(sf::Color::Red);
        window.draw(text1);
        window.draw(text2);
        window.draw(playerText);
        window.display();
    }

    // initialize text and background for new, results window
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Text channel1;
    sf::Text channel2;
    sf::Text channel3;
    sf::Text channel4;
    sf::Text channel5;
    text3.setFont(font);
    text3.setString("Similar Channels:");
    text3.setCharacterSize(30);
    text3.setFillColor(sf::Color::White);
    setText(text3, 400, 25);
    text3.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text4.setFont(font);
    text4.setString("Djikstra Time: " + to_string(dTime) + " ms");
    text4.setCharacterSize(15);
    text4.setFillColor(sf::Color::White);
    setText(text4, 200, 500);
    text4.setStyle(sf::Text::Bold);
    text5.setFont(font);
    text5.setString("BellMan's Time: " + to_string(bTime) + " ms");
    text5.setCharacterSize(15);
    text5.setFillColor(sf::Color::White);
    setText(text5, 600, 500);
    text5.setStyle(sf::Text::Bold);
    channel1.setFont(font);
    channel1.setString("1. " + recs[0].name);
    channel1.setCharacterSize(20);
    channel1.setFillColor(sf::Color::White);
    setText(channel1, 400, 200);
    channel1.setStyle(sf::Text::Bold);
    channel2.setFont(font);
    channel2.setString("2. " + recs[1].name);
    channel2.setCharacterSize(20);
    channel2.setFillColor(sf::Color::White);
    setText(channel2, 400, 250);
    channel2.setStyle(sf::Text::Bold);
    channel3.setFont(font);
    channel3.setString("3. " + recs[2].name);
    channel3.setCharacterSize(20);
    channel3.setFillColor(sf::Color::White);
    setText(channel3, 400, 300);
    channel3.setStyle(sf::Text::Bold);
    channel4.setFont(font);
    channel4.setString("4. " + recs[3].name);
    channel4.setCharacterSize(20);
    channel4.setFillColor(sf::Color::White);
    setText(channel4, 400, 350);
    channel4.setStyle(sf::Text::Bold);
    channel5.setFont(font);
    channel5.setString("5. " + recs[4].name);
    channel5.setCharacterSize(20);
    channel5.setFillColor(sf::Color::White);
    setText(channel5, 400, 400);
    channel5.setStyle(sf::Text::Bold);

    while (resultwindow.isOpen()) { // event loop for results window
        sf::Event event;
        while (resultwindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                resultwindow.close();
            }
        }
        resultwindow.clear(sf::Color::Red);
        resultwindow.draw(text3);
        resultwindow.draw(text4);
        resultwindow.draw(text5);
        resultwindow.draw(channel1);
        resultwindow.draw(channel2);
        resultwindow.draw(channel3);
        resultwindow.draw(channel4);
        resultwindow.draw(channel5);
        resultwindow.display();
    }
    return 0;
}