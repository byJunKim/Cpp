/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.cpp
 * Author: kimbyeo4
 * 
 * Created on November 6, 2017, 9:10 PM
 */
using namespace std;
#include "ResistorList.h"
#include "Node.h"

ResistorList::ResistorList() {
}

ResistorList::ResistorList(const ResistorList& orig) {
}

ResistorList::~ResistorList() {
}

Resistor* ResistorList::getRListHeadptr() {
    return head;
}

//insert resistors to the resistor list

void ResistorList::addResistor(Resistor* Rinserted) {
    if (head == NULL) {
        head = Rinserted;
        numRes++;
        Rinserted->changeNext(NULL);
    } else {
        Resistor* ptr = head;
        while (ptr->getNext() != NULL) {
            ptr = ptr->getNext();
        }
        ptr ->changeNext(Rinserted);
        Rinserted->changeNext(NULL);
        numRes++;
    }
}

//it searches entire node array and finds a resistor and return a pointer to it

Resistor* ResistorList::lookThruRList(string Rname) {
    if (head == NULL) return NULL;
    else {
        Resistor* ptr = head;
        while (ptr != NULL) {
            if (ptr->getName() == Rname)
                return ptr;
            ptr = ptr->getNext();
        }
        //when it gets out of the loop, there wasnt such a resistor
        return NULL;
    }
}

//function to print an entire list of resistors at a node

void ResistorList::printEntireRList(int nodeNum) {
    if (head == NULL) return;
    else {
        Resistor* ptr = head;
        cout << "Connections at node " << nodeNum << ": " << numRes << " resistor(s)"
                << endl;
        //for(int i=0 ;i <numRes; i++){
        while (ptr != NULL) {
            cout << "  " << ptr ->getName() << setfill(' ') << setw(20) << " " <<
                    setfill(' ') << setw(7) << ptr->getResistance() << setprecision(2) <<
                    fixed << " Ohms " << ptr->getLeftIndex() << " -> " << ptr->getRightIndex()
                    << endl;
            ptr = ptr ->getNext();
        }
        return;
    }
}

//function to delete an entire array at a node
//can be used to delete the all resistor lists at every node

void ResistorList::deleteRList(Resistor* dummy) {
    Resistor* ptr = dummy;
    if (ptr == NULL) return;
    deleteRList(ptr->getNext());
    delete ptr;
    ptr = NULL;
    //dummy = NULL;
    numRes = 0;
    return;
}

//function to be used to delete one specific resistor

void ResistorList::deleteOneR(string Rname, int &counter) {

    if (head == NULL) return;
    else {
        Resistor* ptr = head;
        Resistor* fptr = NULL;

        while (ptr != NULL) {
            if (ptr->getName() == Rname) {
                if (ptr == head) { //deleting head
                    head = head->getNext();
                    delete ptr;
                    ptr = NULL;
                    numRes--;
                    counter++;
                    return;
                } else if (ptr ->getNext() == NULL) { //deleting tail
                    delete ptr;
                    ptr = NULL;
                    fptr->changeNext(ptr);
                    fptr = NULL;
                    numRes--;
                    counter++;
                    return;
                } else {
                    fptr->changeNext(ptr->getNext());
                    delete ptr;
                    ptr = NULL;
                    fptr = NULL;
                    numRes--;
                    counter++;
                    return;
                }
            }
            fptr = ptr;
            ptr = ptr->getNext();

        }

        return;
    }
}

//function to get the number of resistors connected at a node

int ResistorList::getNumRes() {
    return numRes;
}

//used to modify a inserted resistor

void ResistorList::modifyR(string Rname, double resVal) {
    Resistor* ptr = head;

    while (ptr != NULL) {
        if (ptr->getName() == Rname) {
            ptr->setResistance(resVal);
        }
        ptr = ptr->getNext();
    }

}

//this function returns sum of resistors connected parallel

double ResistorList::Rparallel() {
    //when calling this function, I already know the head != NULL
    double result = 0.0;
    int counter = 0;
    Resistor* ptr = head;
    while (counter < numRes) {
        result = result + (1 / (ptr->getResistance()));
        ptr = ptr->getNext();
        counter++;
    }

    return (1 / result);
}

//it returns the other end of a resistor connected to a node

int* ResistorList::oppositeNodeArr(int nodeID) {
    int* theOtherIDs = new int[numRes]; //array of opposite side of node id
    Resistor* ptr = head;

    for (int i = 0; i < numRes; i++) {
        if (ptr->getLeftIndex() == nodeID)
            theOtherIDs[i] = ptr->getRightIndex();
        else if (ptr->getRightIndex() == nodeID)
            theOtherIDs[i] = ptr->getLeftIndex();
        ptr = ptr->getNext();
    }
    return theOtherIDs;

}

//function to return an array that includes all the other ends of resistors
//connected to a node

double* ResistorList::getResistanceArr() {
    Resistor* ptr = head;
    double* resistanceArr = new double[numRes];

    for (int i = 0; i < numRes; i++) {
        resistanceArr[i] = ptr->getResistance();
        ptr = ptr->getNext();
    }
    return resistanceArr;
}

