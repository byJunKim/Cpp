

using namespace std;

#include "Node.h"

Node::Node() {
}

Node::~Node() {

}

Node::Node(int nodeid) {
    node_id = nodeid;
    voltage = 0;
    next = NULL;
    set = false;
}

//to get nodeid
int Node::getNodeid() {
    return node_id;
}

//used to add resistors
void Node::addResistor(Resistor* Rinserted) {
    Rlist.addResistor(Rinserted);
}

//get voltage
double Node::getVoltage() {
    return voltage;
}

//get pointer to the ResistorList head pointer
ResistorList* Node::getptrToRList() {

    ResistorList* ptrToRList = &Rlist;

    return ptrToRList;
}

//function to set or change voltage at a node
void Node::setVoltage(double v) {
    voltage = v;
}

//get the next node in the node linked list
Node* Node::getNext() {
    return next;
}

//getting set boolean
bool Node::getSet() {
    return set;
}

//change the set boolean
void Node::changeSet(bool change) {
    set = change;
}

//change next node connected to it
void Node::changeNextptr(Node* object) {
    next = object;
}