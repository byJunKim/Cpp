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
#include "ResistorList.h"
#include "NodeList.h"

/*
 * 
 */
int main(int argc, char** argv) {

    bool err;

    NodeList Nptr;


    string line, command;
    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {
        stringstream lineStream(line);

        lineStream >> ws >> command >> ws;

        if (command == "insertR") {
            insertR(lineStream, err, Nptr);
        } else if (command == "modifyR") {
            modifyR(lineStream, err, Nptr);
        } else if (command == "deleteR") {
            deleteR(lineStream, err, Nptr);
        } else if (command == "printNode") {
            printNode(lineStream, Nptr);
        } else if (command == "printR") {
            printR(lineStream, Nptr);
        } else if (command == "setV") {
            setV(lineStream, err, Nptr);
        } else if (command == "unsetV") {
            unsetV(lineStream, err, Nptr);
        } else if (command == "solve") {
            solve(lineStream, err, Nptr);
        } else {
            cout << "Error: invalid command" << endl;
        }
        cout << "> ";
        command.clear(); //clear the flag of command
        lineStream >> ws; //ignore all white spaces
        lineStream.ignore(1000, '\n'); //clear the string stream
        getline(cin, line);
    }

    
    Nptr.lookThruToDeleteAll();

    Nptr.deleteNodeList((Nptr.getNodeHeadptr()));

    return 0;
}