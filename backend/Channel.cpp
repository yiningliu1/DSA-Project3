#include "Channel.h"
#include <string>
#include <utility>

Channel::Channel(int i, string n, string cntry, int cat, string pic, string prof, int subs) {
    id = i;
    name = n;
    country = cntry;
    category = cat;
    pictureURL = pic;
    profileURL = prof;
    subscribers = subs;
};
