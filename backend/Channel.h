#include <iostream>
#ifndef PROJECT3_CHANNEL_H
#define PROJECT3_CHANNEL_H
using namespace std;

// struct to organize information about each channel
struct Channel {
    int id;
    string name;
    string country;
    int category;
    string pictureURL;
    string profileURL;
    int subscribers;

    Channel(int i, string n, string cntry, int cat, string pic, string prof, int subs);
};


#endif //PROJECT3_CHANNEL_H
