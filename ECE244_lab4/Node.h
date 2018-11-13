/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Resistor.h"
#include "ResistorList.h"

class Node {
private:

    int node_id;
    double voltage = 0;
    ResistorList Rlist; //head pointer of resistor list
    bool set = false;
    Node* next = NULL;


public:
    Node();
    ~Node();
    Node(int nodeid);

    int getNodeid();
    void addResistor(Resistor*);
    double getVoltage();
    ResistorList* getptrToRList();
    void setVoltage(double v);
    Node* getNext();
    bool getSet();
    void changeSet(bool);
    void changeNextptr(Node*);

};

#endif