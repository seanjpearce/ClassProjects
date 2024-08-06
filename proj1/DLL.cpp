//CISC220010 SEAN PEARCE and ANTHONY FERRARO

#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
using namespace std;


DLL::DLL() {
	first = NULL;
    last = NULL;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string taskname, int priority, int hours, int mins) {
	first = new DNode(taskname, priority, hours, mins);
    last = first;
    numTasks = 1;
    tothrs = hours;
    totmin = mins;
}

DLL::~DLL() {
	DNode *temp = first;
    while(temp != NULL) { //while list isn't empty
        first = temp->next;
        delete temp;
        temp = first;
    }
    first = last = NULL;
}

void DLL::push(string taskname, int priority, int hours, int mins) {
	DNode *newNode = new DNode(taskname, priority, hours, mins);
    if(first == NULL) { //if list is empty
        first = newNode;
        last = newNode;
        numTasks = 1;
        tothrs = hours;
        totmin = mins;
        return;
    }
    DNode *temp1 = last;
    while(((temp1->task->priority) > priority) && ((temp1->prev) != NULL)) //traverse the list while priority is lower
        temp1 = temp1->prev;
    DNode *temp2 = temp1->next;
    if(((temp1->task->priority) > priority) && (temp1->prev == NULL)) { //if newNode should be first element
        temp1->prev = newNode;
        newNode->next = temp1;
        newNode->prev = NULL;
        first = newNode;
    } else {
        if (temp2 == NULL) //if newNode should be last element
            last = newNode;
        else //if newNode goes between two elements
            temp2->prev = newNode;
        temp1->next = newNode;
        newNode->next = temp2;
        newNode->prev = temp1;
    }
    addTime(hours, mins); //add time to the list
    numTasks++;
}

Task *DLL::pop() {
    DNode *ret = last;
    Task *rettask = new Task(ret->task->task, ret->task->priority, ret->task->hr, ret->task->min);
    rettask->tasknum = ret->task->tasknum; //creating new task so when deleting the node, still returns the task
    if(last->prev != NULL) { //if only one node in list
        last = ret->prev;
        last->next = NULL;
    }
    numTasks--;
    removeTime(ret->task->hr, ret->task->min);
    delete ret;
    return rettask;
}

int DLL::remove(int tasknum) {
    DNode *current = first;
    while(current != NULL && current->task->tasknum != tasknum) //find the node to remove
        current = current->next;
    if(current == NULL) //if node not found or empty list
        return -1;
    if(numTasks == 1) { //if only one node in list
        last = NULL;
        first = NULL;
    } else if(current->next == NULL) { //if node to be removed is the last node
        last = current->prev;
        last->next = NULL;
    } else if(current->prev == NULL) { //if node to be removed is the first node
        first = current->next;
        first->prev = NULL;
    } else { // if node is anywhere else
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    removeTime(current->task->hr, current->task->min);
    delete current;
    numTasks--;
    return 1;
}

void DLL::addTime(int hours, int mins) {
    totmin += mins;
    tothrs += totmin / 60;
    totmin %= 60;
    tothrs += hours;
}

void DLL::removeTime(int hours, int mins) {
	if(mins > totmin) {
        tothrs--;
        totmin += 60;
    }
    totmin -= mins;
    tothrs -= hours;
}

void DLL::moveUp(int tasknum) {
	DNode *current = first;
    while(current->task->tasknum != tasknum) //find the node to move up
        current = current->next;
    if(current->prev == NULL) { //if the node is first
        first = current->next;
        first->prev = NULL;
        last->next = current;
        current->prev = last;
        last = current;
        current->next = NULL;
        current->task->priority = current->prev->task->priority;
    } else if(current->next == NULL) { //if the node is last
        last = current->prev;
        current->prev = last->prev;
        current->prev->next = current;
        last->prev = current;
        last->next = NULL;
        current->next = last;
        if(current->task->priority > last->task->priority) //if node moved to a higher priority level
            current->task->priority--;
    } else { //if the node anywhere else
        DNode *temp = current->prev;
        current->prev = temp->prev;
        temp->next = current->next;
        temp->prev = current;
        current->next = temp;
        temp->next->prev = temp;
        if(current->prev != NULL) //if current isn't the first node now
            current->prev->next = current;
        else //if current is the first node now
            first = current;
        if(current->task->priority > temp->task->priority) //if node moved to a higher priority level
            current->task->priority--;
    }
}

void DLL::moveDown(int tasknum) {
    DNode *current = first;
    while(current->task->tasknum != tasknum) //find node
        current = current->next;
    if(current->next == NULL) { //if the node is last
        last = current->prev;
        last->next = NULL;
        first->prev = current;
        current->next = first;
        first = current;
        current->prev = NULL;
        current->task->priority = current->next->task->priority;
    } else if(current->prev == NULL) { //if node is first
        first = current->next;
        current->next = first->next;
        current->next->prev = current;
        first->next = current;
        first->prev = NULL;
        current->prev = first;
        if (current->task->priority < first->task->priority) //if node moved to a lower priority level
            current->task->priority++;
    } else { //if node is anywhere else
        DNode *temp = current->next;
        current->next = temp->next;
        temp->prev = current->prev;
        temp->next = current;
        current->prev = temp;
        temp->prev->next = temp;
        if(current->next != NULL) //if current isn't the last node now
            current->next->prev = current;
        else //if current is the last node now
            last = current;
        if(current->task->priority < temp->task->priority) //if node moved to a lower priority level
            current->task->priority++;
    }
}

void DLL::changePriority(int tasknum, int newPriority) {
	DNode *current = first;
    while(current != NULL && current->task->tasknum != tasknum) //find node
        current = current->next;
    int oldPriority = current->task->priority;
    current->task->priority = newPriority;
    if(oldPriority <= newPriority) { //move to a lower priority
        DNode *temp = current->next;
        while(temp != NULL && temp->task->priority < newPriority + 1) { //while it isn't moved far enough
            moveDown(current->task->tasknum);
            temp = current->next;
        }
    } else if(oldPriority > newPriority) { //move to a higher priority
        DNode *temp = current->prev;
        while(temp != NULL && temp->task->priority > newPriority) { //while it isn't moved far enough
            moveUp(current->task->tasknum);
            temp = current->prev;
        }
    }
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
    DNode *current = first;
    while (current != NULL && current->task->priority != priority) //find node
        current = current->next;
    while (current != NULL && current->task->priority == priority) { //list
        *pHours += current->task->hr;
        *pMins += current->task->min;
        current = current->next;
    }
    *pHours += *pMins / 60;
    *pMins %= 60;
}

void DLL::printList() {
	DNode *current = first;
	cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
	while (current != NULL) {
		current->task->printTask();
		current = current->next;
	}
	cout << endl;
}

void DLL::printList(int priority) {
    DNode *current = first;
    int hours = 0, mins = 0;
    listDuration(&hours, &mins, priority);
    cout << "Total Time Required: "<<hours<< ":"<<mins<<endl;
    while (current != NULL && current->task->priority != priority)
        current = current->next;
    while (current != NULL && current->task->priority == priority) {
        current->task->printTask();
        current = current->next;
    }
    cout << endl;
}

void DLL::printReverse() {
    DNode *current = last;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != NULL) {
        current->task->printTask();
        current = current->prev;
    }
    cout << endl;
}
