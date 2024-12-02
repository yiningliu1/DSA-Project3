#include "Channel.h"
#include "Graph.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
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

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int main() {
    // read in all the channels
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Works!");
    sf::RenderWindow resultwindow;
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
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

    while (window.isOpen()) {
        setText(playerText, 400, 250);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (isalpha(event.text.unicode) || isdigit(event.text.unicode) || isspace(event.text.unicode)) {
                    char a = event.text.unicode;
                    playerInput += a;
                }
                playerText.setString(playerInput + "|");
                if (event.text.unicode == 8 && playerInput.length() >= 1) {
                    playerInput.pop_back();
                    playerText.setString(playerInput + "|");
                }
                if (event.text.unicode == 13) {
                    window.close();
                    resultwindow.create(sf::VideoMode(800, 800), "Game Window");
                }
            }
        }

        window.clear(sf::Color::Red);
        window.draw(text1);
        window.draw(text2);
        window.draw(playerText);
        window.display();
    }

    sf::Text text3;
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
    channel1.setFont(font);
    channel1.setString("1");
    channel1.setCharacterSize(20);
    channel1.setFillColor(sf::Color::White);
    setText(channel1, 400, 200);
    channel1.setStyle(sf::Text::Bold);
    channel2.setFont(font);
    channel2.setString("2");
    channel2.setCharacterSize(20);
    channel2.setFillColor(sf::Color::White);
    setText(channel2, 400, 250);
    channel2.setStyle(sf::Text::Bold);
    channel3.setFont(font);
    channel3.setString("3");
    channel3.setCharacterSize(20);
    channel3.setFillColor(sf::Color::White);
    setText(channel3, 400, 300);
    channel3.setStyle(sf::Text::Bold);
    channel4.setFont(font);
    channel4.setString("4");
    channel4.setCharacterSize(20);
    channel4.setFillColor(sf::Color::White);
    setText(channel4, 400, 350);
    channel4.setStyle(sf::Text::Bold);
    channel5.setFont(font);
    channel5.setString("5");
    channel5.setCharacterSize(20);
    channel5.setFillColor(sf::Color::White);
    setText(channel5, 400, 400);
    channel5.setStyle(sf::Text::Bold);

    while (resultwindow.isOpen()) {
        sf::Event event;
        while (resultwindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                resultwindow.close();
            }
        }
        resultwindow.clear(sf::Color::Red);
        resultwindow.draw(text3);
        resultwindow.draw(channel1);
        resultwindow.draw(channel2);
        resultwindow.draw(channel3);
        resultwindow.draw(channel4);
        resultwindow.draw(channel5);
        resultwindow.display();
    }
    srand(time(0));
    return 0;
}