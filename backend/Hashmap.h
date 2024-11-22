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
    const double maxLF = 0.7;
    vector<hashObj*> buckets;

public:
    HashMap();
    int calculateHash(string id);
    void insert(string key, Channel val);
    vector<Channel> retrieve(string key);
    int size();
    bool empty();
    int count(string key);
    void rebalance();
};

#endif //PROJECT3_HASHMAP_H