#include <iostream>
#ifndef PROJECT3_CHANNEL_H
#define PROJECT3_CHANNEL_H
using namespace std;

struct Channel {
    int id;
    string name;
    string country;
    string category;
    string pictureURL;
    string profileURL;
    int numVideos;
    int subscribers;

    Channel(int i, string n, string cntry, string cat, string pic, string prof, int numVid, int subs);


};


#endif //PROJECT3_CHANNEL_H
