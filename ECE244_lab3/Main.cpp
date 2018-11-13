/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kimbyeo4
 *
 * Created on October 16, 2017, 5:26 PM
 */
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"

//global variables
//p is a pointer to the array of pointers which point to resistor objects
//q is a pointer to the array of node objects
Resistor** p = NULL;
Node* q = NULL;

/*
 * 
 */
int main(int argc, char** argv) {

    int maxNodeNumber, maxResistors;
    bool err;
    int rIndex = 0;

    string line, command;
    cout << "> ";
    getline(cin, line);




    while (!cin.eof()) {
        stringstream lineStream(line);

        lineStream >> ws >> command >> ws;

        if (command == "insertR") {
            insertR(lineStream, maxNodeNumber, maxResistors, rIndex, err);
            //if there was error and it could not add resistor in
            //it deletes the dynamically allocated memory
            if (err == false)rIndex++;
            else {
                delete p[rIndex];
                p[rIndex] = NULL;
            }
        } else if (command == "modifyR") {
            modifyR(lineStream, maxResistors, err, rIndex);
        } else if (command == "deleteR") {
            deleteR(lineStream, err, rIndex, maxNodeNumber, maxResistors);
        } else if (command == "printNode") {
            printNode(lineStream, maxNodeNumber);
        } else if (command == "printR") {
            printR(lineStream, maxResistors, rIndex);
        } else if (command == "maxVal") {
            setMaxVal(lineStream, maxNodeNumber, maxResistors, rIndex, err);
        } else {
            cout << "Error: invalid command" << endl;
        }
        cout << "> ";
        command.clear(); //clear the flag of command
        lineStream >> ws; //ignore all white spaces
        lineStream.ignore(1000, '\n'); //clear the string stream
        getline(cin, line);
    }

    //before exiting delete all the objects and arrays and
    //make the pointers point to NULL
    if (rIndex != 0) {
        for (int i = 0; i < rIndex; i++) {
            delete p[i];
            p[i] = NULL;
        }
    }
    delete [] p;
    delete [] q;
    p = NULL;
    q = NULL;

    return 0;
}