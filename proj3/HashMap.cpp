// Name: Sean Pearce and Anthony Ferraro

#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <cmath>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
    numKeys = 0;
    mapSize = 1;
    hashfn = hash1;
    collfn = coll1;
    first = " ";
    collisions = 0;
    hashcoll = 0;
    map = new hashNode*[mapSize];
    for(int i = 0; i < mapSize; i++)
        map[i] = nullptr;
}

hashMap::~hashMap() {
	for(int i=0; i<mapSize; i++) {
		if(map[i] != NULL) {
			delete map[i];
			map[i] = NULL;
		}
	}
	delete [] map;
}

void hashMap::addKeyValue(string k, string v) {
    int index = getIndex(k);
    if (map[index] != nullptr) { //if keyword already exists
        map[index]->addValue(v); //add value to values list
        return;
    }
    numKeys++; //new keyword so increment numKeys
    map[index] = new hashNode(k, v); //new keyword so a new hashnode
    if(numKeys >= (0.7*mapSize)) //if map is 70% full
        reHash();
}

int hashMap::getIndex(string k) {
	int index, hash, coll = 0;
    if(hashfn) //hash 1
        hash = calcHash1(k);
    else //hash 2
        hash = calcHash2(k);
    index = hash; //index so we can keep track of index without changing original hash value
    if(map[index] == nullptr) //if empty spot
        return index;
    hashcoll++; //collision from original hash
    while(map[index] != nullptr and map[index]->keyword != k) { //while not empty and isn't correct keyword
        if(coll > 0) //to not increment if it's first collision (hashcoll)
            collisions++;
        coll++;
        if(collfn) //coll 1
            index = coll1(hash, coll, k);
        else //coll 2
            index = coll2(hash, coll, k);
    }
    return index;
}

int hashMap::calcHash2(string k){ //inefficient hash function
	int h = 0;
    for(int i = k.length()-1; i > -1; i--)
        h += (int) k[i];
    h %= mapSize;
    return h;
}

int hashMap::calcHash1(string k){ //more efficient hash function
	int h = 0;
    for(int i = 0; i < k.length(); i++)
        h = (h * 11 + (int) k[i]) % mapSize;
    return h;
}

void hashMap::getClosestPrime() {
	mapSize *= 2; //double
    while(!prime()) //increment until prime
        mapSize++;
}

bool hashMap::prime() {
    for(int i = 2; i < mapSize/2; i++) //go thru every possible factor and make sure there are none
        if(mapSize % i == 0) //if not prime (found a factor)
            return false;
    return true; //prime
}

void hashMap::reHash() {
    hashNode **keys = map; //get old map info
    int index, keySize = mapSize;
    getClosestPrime(); //double mapSize to next prime
    map = new hashNode*[mapSize]; //new map
    for(int i = 0; i < mapSize; i++) //null out new map
        map[i] = nullptr;
    for(int i = 0; i < keySize; i++) { //rehash old hash values
        if(keys[i] != nullptr) { //if node
            index = getIndex(keys[i]->keyword);
            map[index] = keys[i];
        }
    }
    delete[] keys; //delete old map
}

int hashMap::coll1(int h, int i, string k) { //linear probing
	h = (h + i) % mapSize;
    return h;
}

int hashMap::coll2(int h, int i, string k) { //quadratic probing
	h = (h + i^2) % mapSize;
    return h;
}

void hashMap::printMap() {
	cout << "Hash Map:" << endl;
	for (int i = 0; i < mapSize; i++) {
		// print valid values
		if (map[i] != nullptr) {
			printf("[%6d] ", i);
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
	cout << "Total Keys: " << numKeys << endl;
	cout << "Hash Map Array Size: " << mapSize << endl;
}


