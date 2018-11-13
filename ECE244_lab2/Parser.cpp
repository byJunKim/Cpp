/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kimbyeo4
 *
 * Created on September 27, 2017, 7:59 PM
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

const int MAX_NODE_NUMBER = 5000;
/*
 * 
 */

void insertR(stringstream &lineStream);
void modifyR(stringstream &lineStream);
void deleteR(stringstream &lineStream);
void printNode(stringstream &lineStream);
void printR(stringstream &lineStream);
void printInvalidArg(stringstream &lineStream);
bool isItNumber(stringstream &lineStream);
bool isItNegative(stringstream &lineStream);
bool isItPositive(stringstream &lineStream);

//five different commands will be called in the main

int main(int argc, char** argv) {

    string line, command;
    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {

        stringstream lineStream(line);

        lineStream >> ws >> command >> ws;

        if (command == "insertR") {
            insertR(lineStream);
        } else if (command == "modifyR") {
            modifyR(lineStream);
        } else if (command == "deleteR") {
            deleteR(lineStream);
        } else if (command == "printNode") {
            printNode(lineStream);
        } else if (command == "printR") {
            printR(lineStream);
        } else {
            cout << "Error: invalid command" << endl;
        }
        cout << "> ";
        command.clear();
        getline(cin, line);

    }

    return 0;

}

//insertR checks each of the 4 inputs is valid first
//if they are, see if enough number of inputs is typed

void insertR(stringstream &lineStream) {

    string name;
    double resValue;
    int leftNodeid, rightNodeid;
    int count = 0;
    bool err = false; // this boolean type is to avoid printing multi error messages

    lineStream >> ws; //ignore white spaces
    if (!lineStream.eof() && !err) { //if the stream did not hit end of file and any error hasn't occurred yet
        lineStream >> name>> ws; // read the input as name, and ignore white spaces afterwards too
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
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof() )) { 
            // fail flag checks if the input is invalid and peek checks if there is any character following an input number
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
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' )) { // check if it is a character or other types
            if (!lineStream.eof()) {
                //the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
            }
        }

        if ((leftNodeid < 0 || leftNodeid > MAX_NODE_NUMBER) && !err) {
            cout << "Error: node " << leftNodeid << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else {
            count++; //leftNode id is fine to be read
        }
    }

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> ws;
        lineStream >> rightNodeid; //should not ignore white spaces
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof() )) { // check if it failed and see if there is another thing inputted right after
                //here the mixture of number and character is typed
                printInvalidArg(lineStream);
                err = true;
        }

        if ((rightNodeid < 0 || rightNodeid > MAX_NODE_NUMBER) && !err) {
            cout << "Error: node " << rightNodeid << " is out of permitted range 0-5000" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            err = true;
        } else {
            count++; //rightNodeId is fine to be read
        }
    }

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
    } else if (count < 4 && !err) {
        cout << "Error: too few arguments" << endl;
        lineStream.clear();
        lineStream.ignore(1000, '\n');
    } else {
        if (!err) {
            cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resValue <<
                    " Ohms " << leftNodeid << " -> " << rightNodeid << endl;
        }
    }
}

//modifyR gets name and resistance
//checks each of the 2 inputs is valid first
//if they are, see if they are okay to be printed

void modifyR(stringstream & lineStream) {
    string name;
    double resValue;
    int count = 0;
    bool err = false; //prevents multiple error messages print

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

    lineStream >> ws;
    if (!lineStream.eof() && !err) {
        lineStream >> resValue;
        if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof() )) { // checks if it is valid first and see if there is white space right after
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
            cout << "Modified: resistor " << name << " to " << setprecision(2) << fixed << resValue << " Ohms" << endl;
        }
    }
}

//deleteR gets one input and checks its validity
//if there is no input or input is not valid, it prints one error message in accordance of the priority

void deleteR(stringstream & lineStream) {
    string name;
    int count = 0; // counter tells me how many inputs there are
    bool err = false; //this prevents printing multiple error messages

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> name;
        count++;
    }

    lineStream >> ws;
    if (!lineStream.eof()) count++;

    if (!lineStream.fail() && !err) {
        if (count == 1 && name == "all") {
            cout << "Deleted: all resistors" << endl;
        } else {

            if (count < 1) {
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
            } else if (count > 1) {
                cout << "Error: too many arguments" << endl;
                lineStream.clear();
                lineStream.ignore(1000, '\n');
            } else
                cout << "Deleted: resistor " << name << endl;
        }
    }
}

//printNode should have one input (integer or character)
//checks if it is valid (with - sign? or with invalid character?)
//if input is character it checks whether it is "all" or not

void printNode(stringstream & lineStream) {

    string firstTyped;
    int nodeNum;
    bool err = false;
    bool announced = false;

    lineStream >> ws;
    if (!lineStream.eof()) {
        if (isItNumber(lineStream) || isItNegative(lineStream)) { // if it is a digit (both + and -)
            lineStream >> nodeNum; //input can be both positive and negative
            if (lineStream.fail() || (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof()) ) { //input has a character right after the - sign
                printInvalidArg(lineStream);
                err = true;
            } 
//            else if (lineStream.peek() != ' ' && lineStream.peek() != '\t' ) { //for cases like -5a
//                if (!lineStream.eof()) {
//                    printInvalidArg(lineStream);
//                    err = true;
//                }
//            }

            if ((nodeNum > MAX_NODE_NUMBER || nodeNum < 0) && !err) { // if not the first case it checks its size if it is <=5000
                cout << "Error: node " << nodeNum << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;
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
                    cout << "Print: node " << nodeNum << endl;
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
                    cout << "Print: all nodes" << endl;
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

//gets one input as the resistor name
//checks if only one input is typed

void printR(stringstream & lineStream) {

    string name;
    int count = 0;

    lineStream >> ws;
    if (!lineStream.eof()) {
        lineStream >> name>> ws;
        count++;
    }

    if (!lineStream.eof()) count++;

    if (count == 1 && name == "all") {
        cout << "Print: all resistors" << endl;
    } else {
        if (count < 1) {
            cout << "Error: too few arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');

        } else if (count > 1) {
            cout << "Error: too many arguments" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        } else {
            cout << "Print: resistor " << name << endl;
        }
    }
}

//THis function prints the error message and cleans up the stream flags and ignore whatever was typed

void printInvalidArg(stringstream & lineStream) {
    cout << "Error: invalid argument" << endl;
    lineStream.clear();
    lineStream.ignore(1000, '\n');
}
//checks if input is a digit (>=0)

bool isItNumber(stringstream & lineStream) {

    if ( lineStream.peek() >= '0' && lineStream.peek() <= '9') {
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