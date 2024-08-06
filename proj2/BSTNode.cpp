//Sean Pearce and Anthony Ferraro   CISC210010

#include <iostream>
#include <string>
#include "BSTNode.hpp"
using namespace std;

BSTNode::BSTNode (string t, string auth, int yr, string pub, long long isbn, float rate) { //all null except book
	left = nullptr;
    right = nullptr;
    parent = nullptr;
    book = new Book(t, auth, yr, pub, isbn, rate);
    height = 0;
}
BSTNode::BSTNode() { //set it all to null except book which has a default constructor of its own
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    book = new Book();
    height = 0;
}

BSTNode::~BSTNode(){
	cout <<"Deleting "<<book->title<<endl;
	delete book;
	book = nullptr;
}

void BSTNode::printNode(bool debug) {
	/* takes a boolean to decide whether to print extra information about the node - useful for debugging */
	book->printBook();
	if(debug) {
		cout << "Node: h=" << height ;
		cout << "\n\tParent: " << (parent ? parent->book->title + ": " + parent->book->author : "NODE IS ROOT");
		cout << "\n\tLeft: " << (left ? left->book->title + ": " + left->book->author : "--");
		cout << "\n\tRight: " << (right ? right->book->title + ": " + right->book->author : "--");
		cout << endl << endl;
	}
}



