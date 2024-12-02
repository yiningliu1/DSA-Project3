#include <iostream>
#include <vector>
#include "Channel.h"
#ifndef PROJECT3_HASHMAP_H
#define PROJECT3_HASHMAP_H
using namespace std;

// Hashmap with ids as keys that store vectors of pairs of channels and weights.
struct hashObj {
    string key;
    vector<pair<Channel, int>> val;
    hashObj* next = nullptr;
};

class HashMap {
    int numKeys;
    int bucketCount;
    double loadFact;
    const double maxLF = 0.7;
    vector<hashObj*> buckets;
    void clearBuckets();
    ~HashMap();

public:
    HashMap();
    int calculateHash(string id);
    void insert(string key, pair<Channel, int>& val);
    vector<pair<Channel, int>> retrieve(string& key);
    int size();
    bool empty();
    int count(string key);
    void rebalance();
};

#endif //PROJECT3_HASHMAP_H