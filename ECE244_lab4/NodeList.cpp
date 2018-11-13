/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.cpp
 * Author: kimbyeo4
 * 
 * Created on November 6, 2017, 9:08 PM
 */
//#include "Node.h"
using namespace std;
#define MIN_ITERATION_CHANGE 0.0001
#include "NodeList.h"
#include "ResistorList.h"
#include <cmath>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <iomanip>

NodeList::NodeList() {
}

NodeList::NodeList(const NodeList& orig) {
}

NodeList::~NodeList() {
}

Node* NodeList::getNodeHeadptr() {
    return head;
}

//if node doesnt exist, create new one and return a pointer to it
//if there is, return the pointer to the existing node
Node* NodeList::findOrCreateNode(int id) {

    Node* ptr = head;
    Node* fptr = NULL;
    if (head == NULL) {
        Node* insertedNode = new Node(id);
        head = insertedNode;
        insertedNode ->changeNextptr(NULL);
        ptr = NULL;
        return insertedNode;
    } //No need to make inserted point to NULL
    while ((ptr->getNodeid() <= id)) {
        if (ptr->getNodeid() == id) {
            return ptr;
        }
        fptr = ptr;
        ptr = ptr->getNext();
        if (ptr == NULL) break; //fptr == tail
    }

    //when it gets out of the loop == place the node
    //tail
    //ptr == NULL, fptr == anyNode in middle
    if (ptr == head) { // we know fptr == NULL
        //insert in the front
        Node* insertedNode = new Node(id);
        head = insertedNode;
        insertedNode ->changeNextptr(ptr);
        ptr = NULL;
        return insertedNode;
    }        //ptr != head, insert in between
    else if (ptr != NULL) {
        if (fptr == head) { //insert at the end
            Node* insertedNode = new Node(id);
            head ->changeNextptr(insertedNode);
            insertedNode ->changeNextptr(ptr);
            ptr = NULL;
            fptr = NULL;
            return insertedNode;
        } else { // fptr != head
            Node* insertedNode = new Node(id);
            fptr->changeNextptr(insertedNode);
            insertedNode ->changeNextptr(ptr);
            ptr = NULL;
            fptr = NULL;
            return insertedNode;
        }
    } else { // fptr == tail, ptr == NULL
        if (fptr == head) { //inserting at the end
            Node* insertedNode = new Node(id);
            head->changeNextptr(insertedNode);
            insertedNode ->getNext() == NULL; //optional
            fptr = NULL;
            ptr = NULL;
            return insertedNode;
        } else { //fptr != head but tail
            Node* insertedNode = new Node(id);
            fptr->changeNextptr(insertedNode);
            insertedNode->changeNextptr(NULL); //optional
            ptr = NULL;
            fptr = NULL;
            return insertedNode;
        }
    }


}

//this function is to check if a node with a specific ID exists in the node list
bool NodeList::findID(int id) {

    Node* ptr = head;

    while (ptr != NULL) {
        if (ptr->getNodeid() == id) return true;
        ptr = ptr->getNext();
    }

    return false;

}

//this is to check if there is any node set which enables solve calculation
bool NodeList::searchSetNode() {
    if (head == NULL) return false;
    Node* ptr = head;

    while (ptr != NULL) {
        if (ptr->getSet()) return true;
        ptr = ptr->getNext();
    }
    return false;
}

//this is to find a specific resistor
//if it finds it, return a pointer to the resistor object
//it also calls a public member function of NodeList
Resistor* NodeList::lookThruNode(string Rname) {

    Resistor* Rptr = NULL;
    if (head == NULL) return NULL;
    else {
        Node* ptr = head;
        while (ptr != NULL) {
            Rptr = (ptr->getptrToRList()->lookThruRList(Rname));
            if (Rptr != NULL) return Rptr;
            ptr = ptr->getNext();
        }
        return NULL; //fail to find the same name of the resistor
    }
}


void NodeList::setVoltage(int id, double vol) {
    Node* ptr = head;
    while (ptr != NULL) {
        if (ptr->getNodeid() == id) {
            ptr->setVoltage(vol);
            ptr->changeSet(true);
            return;
        }
        ptr = ptr->getNext();
    }
    cout << "Error: node " << id << " not found" << endl;
}

//unset the voltage, reset the voltage to 0
void NodeList::unSetVoltage(int id) {
    Node* ptr = head;
    while (ptr != NULL) {
        if (ptr->getNodeid() == id) {
            ptr->setVoltage(0.00);
            ptr->changeSet(false);
            return;
        }
        ptr = ptr->getNext();
    }
}

//function to delete the all the connected resistors and nodes
void NodeList::lookThruToDeleteAll() {
    if (head == NULL) return;
    else {
        Node* ptr = head;
        while (ptr != NULL) {
            ptr->getptrToRList()->deleteRList(ptr->getptrToRList()->getRListHeadptr());
            ptr = ptr->getNext();
        }
        this->deleteNodeList(head);
        
        head = NULL;
        return;
    }
}

//function to delete one specific resistor
//does not delete the node
void NodeList::lookThruToDeleteOne(Resistor* RtoDelete) {

    int counter = 0;
    string Rname = RtoDelete -> getName();
    if (head == NULL) return;
    else {
        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr->getptrToRList()->getNumRes() != 0) {
                if (counter == 2) break;
                ptr->getptrToRList()->deleteOneR(Rname, counter);
            }
            ptr = ptr->getNext();
        }


        return;
    }
}

//function to print all resistors connected to each node
void NodeList::printAll() {
    cout << "Print:" << endl;
    Node* ptr = head;
    while (ptr != NULL) {
        ptr->getptrToRList()->printEntireRList(ptr->getNodeid());
        ptr = ptr ->getNext();
    }
    return;
}

//function to print a specific resistor
void NodeList::printOne(int id) {
    if (head == NULL) return;
    else {
        cout << "Print:" << endl;
        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr ->getNodeid() == id) {
                ptr->getptrToRList()->printEntireRList(id);
                return;
            }
            ptr = ptr->getNext();
        }
        return;
    }
}

//to get the number of resistors connected to a node
int NodeList::getNumRes(int id) {
    if (head == NULL) return 0; //what should happen when the node doesnt exist for printNode ?
    else {
        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr ->getNodeid() == id) {
                return ptr ->getptrToRList()->getNumRes();
            }
        }
    }
}

//function to delete the entire node list
void NodeList::deleteNodeList(Node* dummy) {

    Node* ptr = dummy;

    if (head == NULL) return;
    else {
        if (dummy != NULL) {
            deleteNodeList(ptr->getNext());
            delete ptr;
            ptr = NULL;
            return;
        } else return;
    }
}

//function to modify given resistors
void NodeList::modify(string Rname, double resVal, int id_1, int id_2) {
    Node* ptr = head;

    while (ptr != NULL) {
        if (ptr->getNodeid() == id_1 || ptr->getNodeid() == id_2)
            ptr->getptrToRList()->modifyR(Rname, resVal);

        ptr = ptr->getNext();
    }
}

//to get number of unset voltages
int NodeList::numOfUnsetV(){
    int counter = 0;
    Node* ptr = head;

    while (ptr != NULL) {
        if (!ptr->getSet()) counter++;
        ptr = ptr->getNext();
    }
    return counter;

}

//to get an array of node ids where the voltages are not set
int* NodeList::unsetNodesArr() {

    int zeroV, index = 0;
    Node* ptr = head;

    zeroV = this->numOfUnsetV();
    int* nodeArr = new int[zeroV]; //integer array

    while (ptr != NULL) {
        if (ptr->getSet() == false) {
            nodeArr[index] = ptr->getNodeid();
            index++;
        }
        ptr = ptr->getNext();
    }
    return nodeArr;
}

//to get a pointer to a specific node
Node* NodeList::getSpecificNode(int id) {

    Node* ptr = head;
    if (this->findID(id)) {
        while (ptr != NULL) {
            if (ptr->getNodeid() == id) {
                return ptr;
            }
            ptr = ptr->getNext();
        }
    }
}

//computes sum of V/R
double NodeList::computeVOverR(int id, int var) {
    Node* ptr;
    int* otherSideIDs;
    double* resistanceArr;
    double VORsum = 0;

    ptr = this->getSpecificNode(id);

    otherSideIDs = ptr->getptrToRList()->oppositeNodeArr(id);
    resistanceArr = ptr->getptrToRList()->getResistanceArr();

    for (int i = 0; i < ptr->getptrToRList()->getNumRes(); i++) {
        VORsum = VORsum + (this->getVoltage(otherSideIDs[i])) / (resistanceArr[i]);
    }
    delete [] otherSideIDs;
    otherSideIDs = NULL;
    delete [] resistanceArr;
    resistanceArr = NULL;

    return VORsum;
}

//to get a voltage of a node
double NodeList::getVoltage(int id) {
    Node* ptr = head;

    while (ptr != NULL) {
        if (ptr->getNodeid() == id) {
            return (ptr->getVoltage());
        }
        ptr = ptr->getNext();
    }

}

//compute the v_o one iteration
double NodeList::computeV0(int id, int var) {
    double VoverR = computeVOverR(id, var);
    double parallelSum;

    Node* ptr = this->getSpecificNode(id);
    parallelSum = ptr->getptrToRList()->Rparallel();

    return (parallelSum * VoverR); //V at a node

}

//solve the whole network resulting in different voltages
void NodeList::solveNetwork() {
    
    int counter = 1;
    double difference = 1000;
    double oldV, newV;
    Node* ptr;
    Node* fptr = NULL;
    int* node_0V;
    node_0V = this->unsetNodesArr();
    int var = this->numOfUnsetV();
    while (counter != 0) {
        counter = 0;
        for (int i = 0; i < var; i++) {
            ptr = (this->getSpecificNode(node_0V[i]));
            oldV = ptr->getVoltage();
            newV = computeV0(node_0V[i], var);
            difference = abs(newV - oldV);
            ptr->setVoltage(newV);
            if (difference >= MIN_ITERATION_CHANGE) {
                counter++;
            }
        }
    }
    ptr = head;
    
    cout << "Solve:" << endl;
    while (ptr != NULL) {
        cout << "  Node " << ptr->getNodeid() << ": " << fixed << setprecision(2) <<
                ptr->getVoltage() << " V" << endl;
        fptr = ptr;
        ptr = ptr->getNext();

        delete [] node_0V;
        node_0V = NULL;
    }
}

