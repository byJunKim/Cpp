/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: kimbyeo4
 *
 * Created on November 6, 2017, 9:08 PM
 */

#ifndef NODELIST_H
#define NODELIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"

class NodeList {
private:
    Node* head = NULL;

public:
    NodeList();
    NodeList(const NodeList& orig);
    virtual ~NodeList();

    Node* getNodeHeadptr();
    Node* findOrCreateNode(int);
    bool findID(int id);
    bool searchSetNode();
    Resistor* lookThruNode(string Rname);
    void setVoltage(int, double);
    void unSetVoltage(int);
    void lookThruToDeleteAll();
    void lookThruToDeleteOne(Resistor*);
    void printAll();
    void printOne(int);
    int getNumRes(int);
    void deleteNodeList(Node*);
    void modify(string, double, int, int);
    int numOfUnsetV();
    int* unsetNodesArr();
    Node* getSpecificNode(int);
    double computeVOverR(int, int);
    double getVoltage(int);
    double computeV0(int, int);
    void solveNetwork();



};

#endif /* NODELIST_H */

