/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kimbyeo4
 *
 */

#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;
#include "Rparser.h"
#include "Resistor.h"
#include "Node.h"

//makes the global variable available in this cpp file
extern Resistor **p;
extern Node *q;

/*
 * 
 */

//setMaxVal reads maxNodeNumber and maxResistors and store it in the variables
//after checking the inputs validity

void setMaxVal(stringstream &lineStream, int &maxNodeNumber, int &maxResistors, int &rIndex, bool &err) {
    int count = 0;
    err = false; //error detector

    lineStream >> ws; //clear white spaces
    if (!lineStream.eof()) { //check if it reached end of file
        lineStream >> maxNodeNumber; // 
        // checks if it is valid first and see if there is white space right after
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
            printInvalidArg(lineStream);
            err = true;
        } else if (maxNodeNumber <= 0) {
            cout << "Error: maxVal arguments must be greater than 0" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else count++;

        //after reading maxNodeNumber, clear all the white spaces
        lineStream >> ws;
        if (!lineStream.eof() && !err) {
            lineStream >> maxResistors;
            // checks if it is valid first and see if there is white space right after
            if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
                printInvalidArg(lineStream);
                err = true;
            } else if (maxResistors <= 0) {
                cout << "Error: maxVal arguments must be greater than 0" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
            } else count++;
        }

        //after reading maxResistors, clear all the white spaces
        lineStream >>ws;
        if (!lineStream.eof()) { //if there is extra arguments
            cout << "Error: too many arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        }

        if (count < 2 && !err) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        }
    }

    //checks if there is no resistor input
    //if there is, delete the objects and reset all the pointers
    if (rIndex != 0 && !err) {
        //delete each object pointed by the pointer array
        for (int i = 0; i < rIndex; i++) {
            delete p[i];
            p[i] = NULL;
        }
    }
    if (!err) {
        delete [] p; //delete the array of pointers
        delete [] q; //delete the node objects in the array
        p = NULL; //reset pointers
        q = NULL;
        rIndex = 0;
    }

    //as soon as it gets new values for maxNodeNumber and maxResistors
    //it does new dynamic allocations
    if (count == 2 && !err) {
        p = new Resistor*[maxResistors];
        q = new Node[maxNodeNumber + 1];
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is "
                << maxResistors << endl;
    }

}

//checks the input validity and input the proper information to each objects
//of resistors and nodes connected to the resistors

void insertR(stringstream &lineStream, int &maxNodeNumber, int &maxResistors, int rIndex, bool &err) {

    string name;
    double resValue;
    int leftNodeid, rightNodeid;
    int endNodes[2];
    int count = 0;
    err = false; // error detector, prevent printing multiple error messages

    p[rIndex] = new Resistor(); //dynamically allocate one resistor object


    lineStream >> ws; //ignore white spaces
    if (!lineStream.eof() && !err) {
        lineStream >> name>> ws; //read the input as name, and ignore white spaces afterwards
        if (name == "all") {
            cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
            lineStream.clear(); //clear lineStream's flags
            lineStream.ignore(1000, '\n'); //ignore whatever was typed.
            err = true;
        } else
            count++;
    }
    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> ws >> resValue;
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
            // fail flag checks if the input is invalid and 
            //peek checks if there is any character following an input number
            //either it failed or next component is a character
            printInvalidArg(lineStream);
            err = true;
        }

        if (resValue < 0 && !err) { //checking for negative resistance
            cout << "Error: negative resistance" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else count++; //resistor is fine to be put
    }

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> leftNodeid; // should not ignore white spaces
        // check if it is a character or other types
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t')) {
            if (!lineStream.eof()) {
                //the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
            }
        }

        if ((leftNodeid < 0 || leftNodeid > maxNodeNumber) && !err) {
            cout << "Error: node " << leftNodeid << " is out of permitted range 0-" << maxNodeNumber << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else {
            endNodes[0] = leftNodeid;
            count++; //leftNode id is fine to be read
        }
    }

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> ws;
        lineStream >> rightNodeid; //should not ignore white spaces
        // check if it failed and see if there is another thing inputted right after
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
            //here the mixture of number and character is typed
            printInvalidArg(lineStream);
            err = true;
        }

        if ((rightNodeid < 0 || rightNodeid > maxNodeNumber) && !err) {
            cout << "Error: node " << rightNodeid << " is out of permitted range 0-" << maxNodeNumber << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else {
            endNodes[1] = rightNodeid;
            count++; //rightNodeId is fine to be read
        }
    }



    //check if resistor array is full
    if (!err && (rIndex + 1 > maxResistors)) {
        cout << "Error: resistor array is full" << endl;
        err = true;
    }

    if (count < 4 && !err) {
        cout << "Error: too few arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        err = true;
    }


    if (!err) {
        //checks if the node is full
        if (!(q[leftNodeid].canAddResistor(rIndex)) || !(q[rightNodeid].canAddResistor(rIndex))) {
            cout << "Error: node is full" << endl;
            err = true;
        }
    }

    if (!err) { //checks if the same name was already inputted
        for (int j = 0; j < rIndex && !err; j++) {
            if (p[j]->getName() == name) {
                cout << "Error: resistor name already exists" << endl;
                err = true;
            }
        }
    }

    //after getting node indexes, ignore all white spaces
    lineStream >> ws;
    if (!lineStream.eof()) count++; //extra input exists

    if ((leftNodeid == rightNodeid) && !err) {
        cout << "Error: both terminals of resistor connect to node " << leftNodeid << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        err = true;
    }

    if (count > 4 && !err) {
        cout << "Error: too many arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        err = true;
    } else {
        if (!err) {
            p[rIndex]->setName(name); //input resistor name to the array
            p[rIndex]->setResistance(resValue); //input resistance to the array
            p[rIndex]->setNodeConnection(endNodes); //input the nodes connected to the resistor
            //connecting resistor ends to the two nodes
            q[leftNodeid].addResistor(rIndex);
            q[rightNodeid].addResistor(rIndex);
            cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resValue <<
                    " Ohms " << leftNodeid << " -> " << rightNodeid << endl;
        }
    }
}

//modifies the resistance of inputted resistance

void modifyR(stringstream & lineStream, int &maxResistors, bool &err, int &rIndex) {
    string name;
    double resValue, oldResVal;
    int count = 0;
    int nameFoundIndex;
    err = false; //prevents multiple error messages print

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> name; //extracting name
        if (name == "all") {
            cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else
            count++;
    }

    if (rIndex == 0) {
        cout << "Error: resistor " << name << " not found" << endl;
        err = true;
    }

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> resValue;
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
            // checks if it is valid first and see if there is white space right after
            printInvalidArg(lineStream);
            err = true;
        }
        if (resValue < 0 && !err) {
            cout << "Error: negative resistance" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else count++; //resistor is fine to be put
    }

    lineStream >> ws;
    if (!lineStream.eof()) count++;

    if (count > 2 && !err) {
        cout << "Error: too many arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
    } else if (count < 2 && !err) {
        cout << "Error: too few arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
    } else {
        if (!err) {
            //checks if the inputted name exists in the array
            //if there is, save the old resistance to oldResVal
            //and update the resistance value
            if (findResName(maxResistors, nameFoundIndex, name)) {
                oldResVal = p[nameFoundIndex]->getResistance();
                p[nameFoundIndex]->setResistance(resValue);
                cout << "Modified: resistor " << name << " from " << setprecision(2)
                        << fixed << oldResVal << " Ohms to " <<
                        setprecision(2) << fixed << resValue << " Ohms" << endl;
            } else {
                cout << "Error: resistor " << name << " not found" << endl;
                err = true;
            }
        }
    }
}

//deleteR gets one input and checks its validity
//delete function does not actually delete the objects and pointers
//it only reset each object and keep the pointers pointing to the same arrays

void deleteR(stringstream & lineStream, bool err, int &rIndex, int &maxNodeNumber, int&maxResistors) {
    string name;
    int count = 0; // counter tells me how many inputs there are
    err = false; //this prevents printing multiple error messages

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> name >> ws;
        count++;
    }

    if (!lineStream.eof()) count++;

    if (!lineStream.fail() && !err) {
        if (count == 1 && name == "all") {
            if (rIndex != 0) { //checks if there is no input resistor
                for (int i = 0; i < rIndex; i++) {
                    delete p[i];
                    p[i] = NULL;
                }

                for (int i = 0; i < maxNodeNumber + 1; i++) {
                    q[i].clear();
                }
            }

            cout << "Deleted: all resistors" << endl;
            rIndex = 0;

        } else {

            if (count < 1) {
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
                err = true;
            } else if (count > 1) {
                cout << "Error: too many arguments" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
                err = true;
            }
        }
    }
}

//printNode prints all the resistors connected to the node

void printNode(stringstream & lineStream, int &maxNodeNumber) {

    string firstTyped, name;
    int nodeNum, numRes;
    bool err = false;
    bool announced = false; //used to distinguish "all" and integer input for 


    lineStream >> ws;
    if (!lineStream.eof()) {
        if (isItNumber(lineStream) || isItNegative(lineStream)) { // if it is a digit (both + and -)
            lineStream >> nodeNum; //input can be both positive and negative
            if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) { //input has a character right after the - sign
                printInvalidArg(lineStream);
                err = true;
            }

            if ((nodeNum > maxNodeNumber || nodeNum < 0) && !err) { // if not the first case it checks its size
                cout << "Error: node " << nodeNum << " is out of permitted range 0-" << maxNodeNumber << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
                err = true;
            }
            lineStream >> ws;
            if (!lineStream.eof() && !err) {
                cout << "Error: too many arguments" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
                err = true;
            } else {
                if (!err) {
                    //print all the connected resistor to the specified node
                    numRes = q[nodeNum].getNumRes();
                    cout << "Print:" << endl << "Connections at node " << nodeNum <<
                            ": " << numRes << " resistor(s)" << endl;
                    //for loop help print all the resistors connected
                    //to the specific node
                    //numRes tells how many resistors are connected
                    for (int i = 0; i < numRes; i++) {
                        //q[k].connectedRes returns the array of each node index
                        //using the value access to the resistor's private
                        //variables and print them
                        cout << "  " << p[(q[nodeNum].connectedRes())[i]]->getName()
                                << setfill(' ') << setw(20) << " " << setfill(' ') << setw(7) <<
                                p[(q[nodeNum].connectedRes())[i]]->getResistance() << setprecision(2) <<
                                fixed << " Ohms " << p[(q[nodeNum].connectedRes())[i]]->getLeftIndex()
                                << " -> " << p[(q[nodeNum].connectedRes())[i]]->getRightIndex() << endl;
                    }

                    announced = true;
                }
            }
        }//then input starts with a character
        if (!announced && !err) {
            lineStream >> firstTyped >> ws;
            if (firstTyped == "all") {
                if (!lineStream.eof()) { //if there is something -> too many arguments
                    cout << "Error: too many arguments" << endl;
                    lineStream.clear();
                    lineStream.ignore(1000, '\n');
                    err = true;
                } else {
                    cout << "Print:" << endl;
                    //nested for loop prints all the resistors connected to
                    //the defined nodes
                    //outer for loop helps print every single node
                    for (int k = 0; k < maxNodeNumber + 1; k++) {
                        numRes = q[k].getNumRes();
                        cout << "Connections at node " << k <<
                                ": " << numRes << " resistor(s)" << endl;
                        //inner for loop help print all the resistors connected
                        //to the specific node
                        //numRes tells how many resistors are connected
                        for (int i = 0; i < numRes; i++) {
                            //q[k].connectedRes returns the array of each node index
                            //using the value access to the resistor's private
                            //variables and print them
                            cout << "  " << p[(q[k].connectedRes())[i]]->getName()
                                    << setfill(' ') << setw(20) << " " << setfill(' ') << setw(7) <<
                                    p[(q[k].connectedRes())[i]]->getResistance() << setprecision(2) <<
                                    fixed << " Ohms " << p[(q[k].connectedRes())[i]]->getLeftIndex()
                                    << " -> " << p[(q[k].connectedRes())[i]]->getRightIndex() << endl;
                        }
                    }

                }
            } else { //characters other than 'all' is typed
                printInvalidArg(lineStream);
                err = true;
            }

        }
    } else { //if nothing typed after command
        cout << "Error: too few arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        err = true;
    }
}

//checks if the input name is in the array
//if there is print it
//if "all" is inputted, print every single resistor

void printR(stringstream & lineStream, int &maxResistors, int &rIndex) {

    string seekName;
    int count = 0;
    int nameFound;

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> seekName>> ws;
        count++;
    }

    if (!lineStream.eof()) count++;

    if (count == 1 && seekName == "all") {
        cout << "Print:" << endl;
        printAll(rIndex, seekName);

    } else if (rIndex != 0) {
        if (count < 1) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');

        } else if (count > 1) {
            cout << "Error: too many arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else {
            //findResName returns true if it finds the same name in the array
            //also get the index where the same name found by sending
            //a variable by reference
            if (findResName(maxResistors, nameFound, seekName)) {
                cout << "Print:" << endl;
                p[nameFound]->print();
            }
        }
    } else {
        cout << "Error: resistor " << seekName << " not found" << endl;
    }
}

//This function prints the error message and 
//cleans up the stream flags and ignore whatever was typed

void printInvalidArg(stringstream & lineStream) {
    cout << "Error: invalid argument" << endl;
    lineStream.clear();
    lineStream.ignore(1000, '\n');
}
//checks if input is a digit (>=0)

bool isItNumber(stringstream & lineStream) {

    if (lineStream.peek() >= '0' && lineStream.peek() <= '9') {
        return true;
    } else {
        return false;
    }
}

//checks if input starts with a negative sign

bool isItNegative(stringstream & lineStream) {

    if (lineStream.peek() == '-')
        return true;
    else
        return false;

}
//search for the name, return true if there is
//if the name exists take the index

bool findResName(int &maxResistors, int &nameFoundIndex, string &name) {

    for (int i = 0; i < maxResistors; i++) {
        if (p[i]->getName() == name) {
            nameFoundIndex = i;
            return true;
        }
    }
    return false;
}

//this function is for printR function to print all the resistors

void printAll(int &rIndex, string name) {
    if (rIndex >= 0) {
        for (int i = 0; i < rIndex; i++) {
            p[i]->print();
        }
    } else {
        if (name == "all")
            cout << "Print:" << endl;
        else
            cout << "Error: resistor " << name << " not found" << endl;
    }
}