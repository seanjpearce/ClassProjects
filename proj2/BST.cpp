//Sean Pearce and Anthony Ferraro   CISC210010
#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() { //empty tree
	root = nullptr;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) { //tree with root
    root = new BSTNode(title, author, yr, pub, isbn, rate);
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *current = root; //the node we use to traverse thru the tree and find where the new node goes
    BSTNode *last; //the last value of current
    BSTNode *node = new BSTNode(title, author, yr, pub, isbn, rate); //the new node we are inserting
    if (root == nullptr){ //if inserting first node into empty tree
        root = node;
        return;
    }
    while(current != nullptr) { //until we find the spot for the node to be inserted
        last = current; //set last to current before current changes
        if(*node->book >= *current->book) //if node goes on the right of the current node
            current = current->right;
        else //left
            current = current->left;
    }
    if(*node->book >= *last->book) //if node goes on the right of the last node (if it is a right child)
        last->right = node;
    else //if it is a left child
        last->left = node;
    node->parent = last;
    setHeight(root);
}

BSTNode *BST::find(string title, string author) {
	BSTNode *current = root; //node we use to traverse the tree
    Book book = Book(title, author, 0, "", 0, 0);
    while(current != nullptr and *current->book != book) { //while we haven't found the book or the end of the tree
        if(book >= *current->book) //if book should be on the right
            current = current->right;
        else //left
            current = current->left;
    }
    return current; //returns node or nullptr (end of tree, means not found)
}

//same as find above but we search thru once before the loop to not find the same book. not recommenting sorry.
// if you edit one you gotta edit the other because it's the same thing basically
BSTNode *BST::find(string title, string author, BSTNode *start) {
    BSTNode *current = start;
    Book book = Book(title, author, 0, "", 0, 0);
    if(book >= *current->book)
        current = current->right;
    else
        current = current->left;
    while(current != nullptr and *current->book != book) {
        if(book >= *current->book)
            current = current->right;
        else
            current = current->left;
    }
    return current;
}


void BST::printTreeIO(bool debug) { //didn't write this
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root, debug);
	}
}

void BST::printTreeIO(BSTNode *node, bool debug) { //in order goes left, node, right
	if(node == nullptr)
        return;
    printTreeIO(node->left, debug);
    node->printNode(debug);
    printTreeIO(node->right, debug);
}

void BST::printTreePre(bool debug) { //didn't write this
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root, debug);
	}
}

void BST::printTreePre(BSTNode *node, bool debug) { //pre-order goes node, left, right
    if(node == nullptr)
        return;
    node->printNode(debug);
    printTreePre(node->left, debug);
    printTreePre(node->right, debug);
}

void BST::printTreePost(bool debug) { // didn't write this
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root, debug);
	}
}

void BST::printTreePost(BSTNode *node, bool debug) { //post-order goes left, right, node
    if(node == nullptr)
        return;
    printTreePost(node->left, debug);
    printTreePost(node->right, debug);
    node->printNode(debug);
}

void BST::clearTree() { //didn't write this
	if (root == nullptr) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = nullptr;
	}
}

void BST::clearTree(BSTNode *node) { //didn't write this
	if (node == nullptr) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = nullptr;
		clearTree(node->right);
		node->right = nullptr;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
	BSTNode *node = find(title, author);
    while(node != nullptr and node->book->checked_out) {
        //find next book while found book is checked out or book is null (not found)
        node = find(title, author, node);
    }
    if(node == nullptr) //unable to find a book that wasn't checked out
        return false;
    node->book->checked_out = true; //set book to checked out
    return true; //able to find a book that wasn't checked out and check it out
}

bool BST::checkIn(string title, string author) {
    BSTNode *node = find(title, author);
    while(node != nullptr and !(node->book->checked_out)) {
        //find next book while found book is checked in or book is null (not found)
        node = find(title, author, node);
    }
    if(node == nullptr) //unable to find a book that wasn't checked in
        return false;
    node->book->checked_out = false; //set book to checked in
    return true; //able to find a book that wasn't checked in and check it in
}

void BST::updateRating(string title, string author, float newRating) {
    BSTNode *node = find(title, author);
    while(node != nullptr) { //until bottom of the tree, should find all copies of the book
        node->book->rating = newRating; //update rating
        node = find(title, author, node); //find next copy
    }
}


BSTNode *BST::removeNoKids(BSTNode *node) {
	if(node->parent == nullptr) { //if root
        root = nullptr; //empty tree
        return node;
    }
    if(node->parent->left == node) //if node is left child
        node->parent->left = nullptr;
    else //if node is right child
        node->parent->right = nullptr;
    setHeight(root);
    node->parent = nullptr;
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
	if(leftFlag) { //if node has left child
        node->left->parent = node->parent;
        if(node->parent) { //if node is not root
            if(node->parent->left == node) //if node is a left child
                node->parent->left = node->left;
            else //if node is a right child
                node->parent->right = node->left;
        } else //if node is root
            root = node->left;
    } else { //if node has right child
        node->right->parent = node->parent;
        if(node->parent) { //if node is not root
            if(node->parent->left == node) //if node is left child
                node->parent->left = node->right;
            else //if node is a right child
                node->parent->right = node->right;
        } else //if node is root
            root = node->right;
    }
    setHeight(root);
    return node;
}

BSTNode *BST::remove(string title, string author) {
	BSTNode *node = find(title, author);
    if(node == nullptr) //if node wasn't found
        return nullptr;
    if(node->left == nullptr and node->right == nullptr) //if node has no children
        return removeNoKids(node);
    else if(node->left != nullptr and node->right == nullptr) //if node has a left child
        return removeOneKid(node, true);
    else if(node->left == nullptr and node->right != nullptr) //if node has a right child
        return removeOneKid(node, false);
    //here down is if node has two children
    BSTNode *current = node->right; //current will replace node
    while(current->left != nullptr) //find left most child of immediate right node (to find node to replace
        current = current->left;
    if(current->parent->right != current) { //if current(replacement) is not immediate right node
        current->parent->left = current->right;
        if(current->right) //if current has a right node
            current->right->parent = current->parent;
        current->right = node->right;
    }
    if(node->parent) { //if node is not root
        if(node->parent->left == node) //if node is a left child
            node->parent->left = current;
        else //right
            node->parent->right = current;
    } else //if node is root
        root = current;
    current->parent = node->parent;
    current->left = node->left;
    if(current->left) //if current has a left child
        current->left->parent = current;
    if(current->right) //if current has a right child
        current->right->parent = current;
    setHeight(root);
    return node;
}

//recursive function that sets all the nodes below to zero, then goes to all leaves and works its way up
//setting all the leaves to the correct height and breaking when it finds a node that has a higher height
void BST::setHeight(BSTNode *node) {
    node->height = 0; //set height of node to zero
    if(node->left) //if left child
        setHeight(node->left);
    if(node->right) //if right child
        setHeight(node->right);
    if(node->left == nullptr and node->right == nullptr){ //if leaf node
        BSTNode *current = node;
        int i = 1;
        while(current != nullptr) { //until you reach the top of the tree
            if(current->height > i) //if height > height we set it too
                break;
            current->height = i;
            i++;
            current = current->parent;
        }
    }
}

