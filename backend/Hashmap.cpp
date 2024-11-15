#include "Hashmap.h"
#include <iostream>
#include <vector>
HashMap::HashMap() {

}

void HashMap::insert(string key, vector<Channel> val) {

}

vector<Channel> HashMap::retrieve(string key) {
    return vector<Channel>();
}

int HashMap::size() {
    return 0;
}

bool HashMap::empty() {
    return false;
}

int HashMap::count(string key) {
    return 0;
}


int Hashmap::hash_function(string id){
    unsigned long hash = 0;
    for (auto c : id){
        hash = hash + static_cast<int>(c);
    }

    return hash;
}

