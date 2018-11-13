


#ifndef RESISTOR_H
#define RESISTOR_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Resistor.h"
//#include "Rparser.h"

class Resistor {
    // friend class NodeList;
    // friend class ResistorList;
    //  friend class Node;
private:
    double resistance = 0.0; // resistance (in Ohms)
    string name = "empty"; // name is initialized to "empty"
    int leftNodeID;
    int rightNodeID;
    // int index = -1; //index of resistor is initialized to -1
    Resistor* next = NULL;
public:

    Resistor();

    Resistor(string, double, int, int);
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects

    ~Resistor(); //destructor

    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    int getLeftIndex();
    int getRightIndex();
    
    //sets the resistor name to the private string name
    void setName(string name_);

    //set the resistance
    void setResistance(double resistance_);
    Resistor* getNext();
    void changeNext(Resistor*);
};

#endif /* RESISTOR_H */

