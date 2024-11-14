//
// Created by lyini on 11/14/2024.
//
#include "Hashmap.h"

int Hashmap::hash_function(string id){
    unsigned long hash = 0;
    for (auto c : id){
        hash = hash + static_cast<int>(c);
    }

    return hash;
}

