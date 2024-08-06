//CISC220010 SEAN PEARCE and ANTHONY FERRARO

#include <iostream>
#include "DNode.hpp"
using namespace std;


DNode::DNode() {
    task = NULL;
    prev = NULL;
    next = NULL;
}

DNode::DNode(string taskname, int priority, int hours, int mins) {
    task = new Task(taskname, priority, hours, mins);
    prev = NULL;
    next = NULL;
}

DNode::~DNode() {
	cout << "deleting node with task " << task->tasknum << endl;
	delete task;
	prev = NULL;
	next = NULL;
}
