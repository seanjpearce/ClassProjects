// Name: Sean Pearce and Anthony Ferraro

#include "HashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


hashNode::hashNode(string s) {
	keyword = s;
	valuesSize = 100;
    values = new string[valuesSize];
	currSize = 0;
	srand(time(NULL));
}

hashNode::hashNode() {
	keyword = "";
	valuesSize = 100;
    values = new string[valuesSize];
	currSize = 0;
	srand(time(NULL));
}

hashNode::hashNode(string s, string v) {
	keyword = s;
    valuesSize = 100;
    values = new string[valuesSize];
	values[0] = v;
	currSize = 1;
}

hashNode::~hashNode() {
	delete [] values;
}

void hashNode::addValue(string v) {
	if(currSize == valuesSize) //if values array is full
        dblArray(); //double
    values[currSize] = v; //fill in next open spot
    currSize++; //increment
}

void hashNode::dblArray() {
	valuesSize *= 2; //double size of values
    string *oldValues = values; //old array of values
    values = new string[valuesSize]; //new array of double size
    for(int i = 0; i < currSize; i++) //fill new array from old array
        values[i] = oldValues[i];
    delete[] oldValues;
}

string hashNode::getRandValue() {
    return values[rand() % currSize]; //random number between 0 and currSize
}
