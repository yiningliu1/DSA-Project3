#include "Hashmap.h"
#include <iostream>
#include <vector>
HashMap::HashMap() {
    buckets.resize(20, nullptr);
    numKeys = 0;
    bucketCount = 20;
    loadFact = 0;
}

void HashMap::insert(string key, pair<Channel, int>& val) {
    int hash = calculateHash(key); // this will be the hash that is calculated
    bool isNew = true;
    if (buckets[hash]) {
        hashObj* currObj = buckets[hash];
        hashObj* prevObj = buckets[hash];
        while(currObj) {
            if (currObj->key == key) {
                isNew = false;
                currObj->val.push_back(val);
                break;
            }
            if (!currObj->next) break;
            prevObj = currObj;
            currObj = currObj->next;
        }
        if (isNew) {
            hashObj* newObj = new hashObj();
            newObj->next = nullptr;
            newObj->key = key;
            newObj->val.push_back(val);
            prevObj->next = newObj;
        }
    } else {
        hashObj* newObj = new hashObj();
        newObj->next = nullptr;
        newObj->key = key;
        if (val.second == -1)
            newObj->val = {};
        else
            newObj->val.push_back(val);

        buckets[hash] = newObj;
    }
    if (isNew) {
        numKeys++;
        loadFact = (double)numKeys/bucketCount;
        if (loadFact >= maxLF) {
            rebalance();
        }
    }
}

vector<pair<Channel, int>> HashMap::retrieve(string& key) {
    int hash = calculateHash(key); // calculate hash
    hashObj* currObj = buckets[hash];
    while(currObj) {
        if (currObj->key == key) return currObj->val;
        currObj = currObj->next;
    }
    return {};
}

int HashMap::size() {
    return numKeys;
}

bool HashMap::empty() {
    return numKeys == 0;
}

int HashMap::count(string key) {
    int hash = calculateHash(key); // calculate hash
    hashObj* currObj = buckets[hash];
    while(currObj) {
        if (currObj->key == key) return 1;
        currObj = currObj->next;
    }
    return 0;
}

void HashMap::rebalance() {
    vector<hashObj*> newVect(buckets.size()*2, nullptr);
    bucketCount *= 2;
    loadFact /= 2;
    for (auto i: buckets) {
        if (!i) continue;
        hashObj* currObj = i;
        while (currObj) {
            int hash = calculateHash(currObj->key); // Recalculate hash for the resized array
            if (!newVect[hash]) {
                newVect[hash] = currObj;
            } else {
                hashObj* temp = newVect[hash];
                while (temp->next) temp = temp->next;
                temp->next = currObj;
            }
            hashObj* nextObj = currObj->next;
            currObj->next = nullptr;
            currObj = nextObj;
        }
    }
    clearBuckets();
    buckets = std::move(newVect);
}

void HashMap::clearBuckets() {
    for (hashObj* obj : buckets) {
        while (obj) {
            hashObj* next = obj->next;
            delete obj;
            obj = next;
        }
    }
}


int HashMap::calculateHash(string id) {
    int hash = 0;
    for (char c: id) {
        hash += c;
    }
    hash %= bucketCount;
    return hash;
}

HashMap::~HashMap() {
    clearBuckets();
}