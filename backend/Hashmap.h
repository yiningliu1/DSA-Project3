#include <iostream>
#include <vector>
#include "Channel.h"
#ifndef PROJECT3_HASHMAP_H
#define PROJECT3_HASHMAP_H
using namespace std;

struct hashObj {
    string key;
    vector<Channel> val;
    hashObj* next = nullptr;
};

class HashMap {
    int numKeys;
    int bucketCount;
    double loadFact;
    double maxLF = 0.7;
    vector<hashObj*> buckets;

public:
    HashMap();
    void insert(string key, vector<Channel> val = {});
    vector<Channel> retrieve(string key);
    int size();
    bool empty();
    int count(string key);
    int hash_function(string id);
};

#endif //PROJECT3_HASHMAP_H