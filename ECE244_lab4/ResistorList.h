/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: kimbyeo4
 *
 * Created on November 6, 2017, 9:10 PM
 */


#ifndef RESISTORLIST_H
#define RESISTORLIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Resistor.h"

class ResistorList {
    friend class Node;
private:
    Resistor* head = NULL;
    int numRes = 0;

public:
    ResistorList();
    ResistorList(const ResistorList& orig);
    virtual ~ResistorList();

    void addResistor(Resistor*);
    Resistor* lookThruRList(string name);
    Resistor* getRListHeadptr();
    void printEntireRList(int);
    int getNumRes();
    void deleteRList(Resistor*);
    void deleteOneR(string, int &);
    // void dropOneConnection(string Rname);
    double Rparallel();
    //int theOtherNodeID(string, int);
    void modifyR(string, double);
    int* oppositeNodeArr(int);
    double* getResistanceArr();

};

#endif /* RESISTORLIST_H */

