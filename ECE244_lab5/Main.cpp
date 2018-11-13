
#include <iostream>
#include <sstream>
#include "TreeDB.h"
#include "DBentry.h"

using namespace std;


int main(int argc, char** argv) {

    string line, command;
    TreeDB BST;
    DBentry* entry;
    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {
        stringstream lineStream(line);
        lineStream >> ws >> command;

        if (command == "insert") {
            unsigned int IPaddress;
            string status, name;
            lineStream >> ws >> name >> ws >> IPaddress >> ws >> status;

            entry = BST.find(name);
            if (entry != NULL) {
                cout << "Error: entry already exists" << endl;
            } else {
                if (status == "active") {
                    entry = new DBentry(name, IPaddress, 1);
                } else
                    entry = new DBentry(name, IPaddress, 0);
                BST.insert(entry);
                cout << "Success" << endl;
            }
        } else if (command == "find") {
            string name;
            lineStream >> ws >> name;
            entry = BST.find(name);

            if (entry == NULL) {
                cout << "Error: entry does not exist" << endl;
            } else {
                cout << *entry;
            }
        } else if (command == "remove") {
            string name;
            lineStream >> ws >> name;

            entry = BST.find(name);
            if (entry == NULL) {
                cout << "Error: entry does not exist" << endl;
            } else {
                BST.remove(name);
                cout << "Success" << endl;
            }
        } else if (command == "printall") {
            cout << BST;
        } else if (command == "printprobes") {
            string name;

            lineStream >> ws >> name;
            entry = BST.find(name);
            if (entry == NULL) {
                cout << "Error: entry does not exist" << endl;
            } else {
                BST.printProbes();
            }

        } else if (command == "removeall") {
            BST.clear();
            cout << "Success" << endl;
        } else if (command == "countactive") {
            BST.countActive();
        } else if (command == "updatestatus") {
            string name, status;
            bool active = true;
            lineStream >> ws >> name >> ws >>status;
            entry = BST.find(name);

            if (entry == NULL) {
                cout << "Error: entry does not exist" << endl;
            } else {
                if (status == "active") {
                    if (!(entry->getActive())) {
                        entry->setActive(active);
                    }
                } else { // original status was true
                    if (entry->getActive()) {
                        entry ->setActive(!active);
                    }
                }

                cout << "Success" << endl;
            }
        } else {
            cout << "Invalid Command" << endl;
        }
        cout << "> ";
        command.clear(); //clear the flag of command
        lineStream >> ws; //ignore all white spaces
        lineStream.ignore(1000, '\n'); //clear the string stream
        getline(cin, line);

    }
    BST.clear();

    return 0;
}

