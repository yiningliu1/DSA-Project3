#include "Hashmap.h"
#include <iostream>
#include <vector>
HashMap::HashMap() {
    vector<hashObj*> newBuckets(20, nullptr);
    buckets = newBuckets;
    numKeys = 0;
    bucketCount = 20;
    loadFact = 0;
}

void HashMap::insert(string key, vector<Channel> val) {
    int hash; // this will be the hash that is calculated
    bool isNew = true;
    if (buckets[hash]) {
        hashObj* currObj = buckets[hash];
        while(true) {
            if (currObj->key == key) {
                isNew = false;
                currObj->val = val;
                break;
            }
            if (!currObj->next) break;
            currObj = currObj->next;
        }
        if (isNew) {
            hashObj newObj;
            newObj.next = nullptr;
            newObj.key = key;
            newObj.val = val;
            currObj->next = &newObj;
        }
    } else {
        hashObj newObj;
        newObj.next = nullptr;
        newObj.key = key;
        newObj.val = val;
        buckets[hash] = &newObj;
    }
    if (isNew) {
        numKeys++;
        loadFact = (double)numKeys/bucketCount;
        if (loadFact >= maxLF) {
            rebalance();
        }
    }
}

vector<Channel> HashMap::retrieve(string key) {
    int hash;
    hashObj* currObj = buckets[hash];
    while(currObj) {
        if (currObj->key == key) break;
        currObj = currObj->next;
    }
    if (currObj) return currObj->val;
    else return {};
}

int HashMap::size() {
    return numKeys;
}

bool HashMap::empty() {
    return numKeys > 0;
}

int HashMap::count(string key) {
    return 0;
}

void HashMap::rebalance() {

}
