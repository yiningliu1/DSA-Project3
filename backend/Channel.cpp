#include "Channel.h"
#include <string>
#include <utility>

Channel::Channel(int i, string n, string cntry, int cat, string pic, string prof, int subs)
: id(i), name(std::move(n)), country(std::move(cntry)), category(cat), pictureURL(std::move(pic)), profileURL(std::move(prof)), subscribers(subs) {};
