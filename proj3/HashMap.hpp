// Name: Sean Pearce and Anthony Ferraro
#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_


#include "HashNode.hpp"

class hashMap {
	friend class makeModel;
	hashNode **map;  //Note that this is a dynamically 
			//allocated array of pointers to hash Nodes.  It 
			//is not a matrix.  I made it a pointer to an 
			//array of pointers to nodes because I didn't 
			//want to have to delete every hash Node and 
			//then create a new one when I rehashed the 
			//array. You still need to rehash the node, but
			//you won't have to recreate the node with all of
			//its values, at least.
	string first; // for first keyword for printing to a file
	int numKeys;  // Number of keys currently in the hashMap
	int mapSize;  // total size of the hashMap array
	bool hashfn;  // a bool indicating whether to use hash 
			//function 1 or hash function 2 (we're comparing 
			//hash function efficiencies)
	bool collfn;  // a bool indicating whether to use the 
			//collision function 1 or the collision function 
			//2 (we're also comparing the efficiency of 
			//different collision functions)
	int collisions;  // number of collisions using the 
			//collision-handling method
	int hashcoll; //number of initial collisions using just 
			//the hash function

public:
	hashMap(bool hash1, bool coll1);  // when creating the 
			//map, make sure you initialize the values to 
			//NULL so you know whether that index has a key 
			//in it or is set to NULL
	~hashMap();
	void addKeyValue(string k, string v);
			// updates the hashmap with the key-value pair
			// by calling getIndex()
			// If the key is already in the map, then the
			// values list for the key is updated.
			// Otherwise, creates a new node and adds it to
			// the map at the given index and adds the
			// value to the values list
			// This method also checks the load, and if the 
			// load factor is over 70%, it calls the reHash 
			// method to create a new longer map array and 
			// rehash the values
	int getIndex(string k); // selects calcHash and a collision
			// function based on to calculate and 
			// return the index of the keyword k in the 
			// hashmap array or the index of the first empty 
			// space hashed/probed if k is not found (e.g., 
			// if it is being added to the hashmap)
			// Note: addKeyValue is the function that actually
			// adds the key to the hashmap if it doesn't exist
			// or adds the value to the list of values if it
			// does already exist. This function is called by
			// the writeFile function for output generation.
	int calcHash1(string k);  // hash function 1
	int calcHash2(string k);  // hash function 2
	void getClosestPrime();  // Gets the prime number closest 
			//to double the map size AND updates the map
			//size to that. I used binary search and an
			//array of primes to find the closest prime to 
			//double the map Size, and then set mapSize to 
			//that new prime - you can find the prime in
			//another way if you choose (e.g., double the
			//current size and start checking numbers to see
			// if they're prime)
	void reHash();  // when size of array is at 70%, double
			// array size with getClosestPrime() and rehash keys
	int coll1(int h, int i, string k);  // a method for 
			// handling collisions (when index is already used)
	int coll2(int h, int i, string k);  // a different method 
			// for dealing with collisions
	void printMap();  //Prints out the valid items in the map
    bool prime();
};


#endif /* HASHMAP_HPP_ */
