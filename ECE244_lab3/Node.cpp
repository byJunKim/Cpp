
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
#include "Resistor.h"
#include "Node.h"
#include "Rparser.h"

Node::Node() {
}

Node::~Node() {
}

bool Node::canAddResistor(int rIndex) {
    if (numRes < 5) {
        return true;
    } else
        return false;
}

void Node::addResistor(int rIndex) {
    if (canAddResistor(rIndex)) {
        resIDArray[numRes] = rIndex;
        numRes++;
    }
}

int Node::getNumRes() {
    return numRes;
}

int* Node::connectedRes() {
    return resIDArray;
}

void Node::clear() {
    for (int i = 0; i <= numRes; i++) {
        resIDArray[i] = -1;
    }
    numRes = 0;
}
