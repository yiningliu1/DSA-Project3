#include "Channel.h"
#include <string>
#include <utility>

Channel::Channel(string i, string n, string cntry, string cat, string pic, string prof, int numVid, int subs)
: id(std::move(i)), name(std::move(n)), country(std::move(cntry)), category(std::move(cat)), pictureURL(std::move(pic)), profileURL(std::move(prof)), numVideos(numVid), subscribers(subs) {};
