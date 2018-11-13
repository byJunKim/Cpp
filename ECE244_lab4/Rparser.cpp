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

#define MIN_ITERATION_CHANGE 0.0001
using namespace std;
#include "Rparser.h"
#include "NodeList.h"


/*
 * 
 */

//creates resistor object & 2 node objects after error checking
//after creating the nodes add resistors to the assigned node
void insertR(stringstream &lineStream, bool &err, NodeList &Nptr) {

    string name;
    double resValue;
    Resistor* sameResistor = NULL;
    int leftNodeid, rightNodeid;
    int count = 0;
    err = false; // error detector, prevent printing multiple error messages


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

    sameResistor = Nptr.lookThruNode(name);

    if (!err && sameResistor != NULL) {
        cout << "Error: resistor " << name << " already exists" << endl;
        err = true;
    }


    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> resValue;
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
        } else count++;

        lineStream >> ws;
        if (!lineStream.eof() && !err) {
            lineStream >> ws;
            lineStream >> rightNodeid; //should not ignore white spaces
            // check if it failed and see if there is another thing inputted right after
            if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
                //here the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
            } else count++;
        }

        lineStream >> ws;
        if (!lineStream.eof()) count++; //extra input exists

        if (count < 4 && !err) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        }

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
                //            endNodes[0] = leftNodeid;
                //            endNodes[1] = rightNodeid;
                //creating pointers to node objects
                Node* node1 = Nptr.findOrCreateNode(leftNodeid);
                Node* node2 = Nptr.findOrCreateNode(rightNodeid);
                Resistor* insertedR1 = new Resistor(name, resValue, leftNodeid, rightNodeid);
                Resistor* insertedR2 = new Resistor(name, resValue, leftNodeid, rightNodeid);
                node1 -> addResistor(insertedR1);
                node2 -> addResistor(insertedR2);

                //            insertedR1 =NULL;
                //            insertedR2 =NULL;
                //            node1 = NULL;
                //            node2 = NULL;
                //inserting to the node list

                cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resValue <<
                        " Ohms " << leftNodeid << " -> " << rightNodeid << endl;
            }
        }
    }
}

//modifies the resistance of inputted resistance
void modifyR(stringstream & lineStream, bool &err, NodeList &Nptr) {
    string name;
    Resistor* ptr;
    double resValue, oldResVal;
    int count = 0, secondEnd;
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

    ptr = Nptr.lookThruNode(name);

    if (ptr == NULL) {
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
    } else { //modify
        if (!err) {
            oldResVal = ptr ->getResistance();
            ptr ->setResistance(resValue);
            Nptr.modify(ptr->getName(), ptr->getResistance(), ptr->getLeftIndex(), ptr->getRightIndex());
            cout << "Modified: resistor " << name << " from " << oldResVal << " Ohms to "
                    << resValue << " Ohms" << endl;
        }
    }

}

//delete one specific resistor object or the whole resistors in the network
//the nodes will not reset
void deleteR(stringstream & lineStream, bool &err, NodeList &Nptr) {
    string name;
    int count = 0; // counter tells me how many inputs there are
    err = false; //this prevents printing multiple error messages
    Resistor* seekingResistor;

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> name >> ws;
        count++;
    }

    if (!lineStream.eof()) count++;

    if (!lineStream.fail() && !err) {
        if (count == 1 && name == "all") {
            Nptr.lookThruToDeleteAll();
            cout << "Deleted: all resistors" << endl;

        } else if (count == 1) {
            seekingResistor = Nptr.lookThruNode(name);
            if (seekingResistor == NULL) {
                cout << "Error: resistor " << name << " not found" << endl;
                err = true;
            } else {
                Nptr.lookThruToDeleteOne(seekingResistor);
                cout << "Deleted: resistor " << name << endl;
            }
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
void printNode(stringstream & lineStream, NodeList &Nptr) {

    string firstTyped, name;
    int nodeNum, numRes;
    bool err = false;
    bool announced = false; //used to distinguish "all" and integer input for 


    lineStream >> ws;
    if (!lineStream.eof()) {
        if (isItNumber(lineStream)) { // if it is a digit
            lineStream >> nodeNum; //input can be both positive and negative
            if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) { //input has a character right after the - sign
                printInvalidArg(lineStream);
                err = true;
            }

            if (!(Nptr.findID(nodeNum))) {
                cout << "Error: node " << nodeNum << " not found" << endl;
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
                    Nptr.printOne(nodeNum);
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
                    Nptr.printAll();
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

//print a specified resistor
void printR(stringstream & lineStream, NodeList &Nptr) {

    string seekName;
    int count = 0;
    Resistor* seekResistor;

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> seekName>> ws;
        count++;
    }

    if (!lineStream.eof()) count++;
    if (count < 1) {
        cout << "Error: too few arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');

    } else if (count > 1) {
        cout << "Error: too many arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
    } else {
        seekResistor = Nptr.lookThruNode(seekName);
        if (seekResistor != NULL) {
            cout << "Print:" << endl;
            cout << seekResistor -> getName() << setfill(' ') << setw(20) << " " << setfill(' ') << setw(7)
                    << seekResistor -> getResistance() << " Ohms " << seekResistor -> getLeftIndex()
                    << " -> " << seekResistor ->getRightIndex() << endl;
        } else {
            cout << "Error: resistor " << seekName << " not found" << endl;
        }
    }

}

//setting the voltage of a specified node to input voltage value
void setV(stringstream & lineStream, bool &err, NodeList & Nptr) {

    double voltage;
    int nodeid, count = 0;
    err = false;

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> nodeid;

        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t')) {
            if (!lineStream.eof()) {
                //the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
            }
        } else count++;
    }

    if (!(Nptr.findID(nodeid))) {
        cout << "Error: node " << nodeid << " not found" << endl;
        err = true;
    }

    lineStream >> ws;
    if (!lineStream.eof() && !err) {

        lineStream >> voltage;
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof())) {
            // fail flag checks if the input is invalid and
            //peek checks if there is any character following an input number
            //either it failed or next component is a character
            printInvalidArg(lineStream);
            err = true;
        } else count++;

    }

    if (!err) {

        if (count > 2) {
            cout << "Error: too many arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else if (count < 2) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else {
            Nptr.setVoltage(nodeid, voltage);
            cout << "Set: node " << nodeid << " to " << setprecision(2) << fixed
                    << voltage << " Volts" << endl;
        }

    }



}

//unset the voltage of a specified node, setting it back to 0
void unsetV(stringstream & lineStream, bool &err, NodeList & Nptr) {
    int nodeid, count = 0;
    err = false;
    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> nodeid;

        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t')) {
            if (!lineStream.eof()) {
                //the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
            } else count++;
        }
    }

    if (!(Nptr.findID(nodeid))) {
        cout << "Error: node " << nodeid << " not found" << endl;
        err = true;
    }


    lineStream >>ws;
    if (!err) {
        if (count > 1) {
            cout << "Error: too many arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else if (count < 1) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else {
            Nptr.setVoltage(nodeid, 0);
            cout << "Unset: the solver will determine the voltage of node "
                    << nodeid << endl;
        }
    }
}

//solve voltages of nodes that are unset depending on the voltage of the other
//end of node connected through a resistor
void solve(stringstream &lineStream, bool &err, NodeList &Nptr) {

    err = false;
    if (!(Nptr.searchSetNode())) {
        cout << "Error: no nodes have their voltage set" << endl;
    } else
        Nptr.solveNetwork();
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