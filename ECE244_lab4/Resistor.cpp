


using namespace std;
#include "Resistor.h"

Resistor::Resistor() {
}

//initializing constructor

Resistor::Resistor(string name_, double resistance_, int leftEnd, int rightEnd) {
    name = name_;
    resistance = resistance_;
    leftNodeID = leftEnd;
    rightNodeID = rightEnd;
    next = NULL;
}

//destructor

Resistor::~Resistor() {
}


string Resistor::getName()const {
    return name;
}

double Resistor::getResistance() const {
    return resistance;
}

int Resistor::getLeftIndex() {
    return leftNodeID;
}

int Resistor::getRightIndex() {
    return rightNodeID;;
}

void Resistor::setName(string name_) {
    name = name_;
}

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

//get next resistor node in the linked list
Resistor* Resistor::getNext() {
    return next;
}

//change next resistor in the linked list
void Resistor::changeNext(Resistor* object) {
    next = object;
}