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

#define MAX_RESISTORS_PER_NODE 5

class Node {
private:

    int numRes = 0; // number of resistors currently connected to node
    int resIDArray[MAX_RESISTORS_PER_NODE] = {-1, -1, -1, -1, -1}; // stores the index of each resistor connected

public:
    Node();
    ~Node();

    //this function returns the number of resistors connected to the node index
    int getNumRes();

    // Checks to see if the resistor can be added to position rIndex
    // in the resistor array. Returns true if yes, otherwise false.
    bool canAddResistor(int rIndex);

    // Updates resIDArray to make the resistor in position rIndex in
    // the resistor array connected to this node.
    void addResistor(int rIndex);

    //returns the whole array of size 5  
    int* connectedRes();

    //reset the node objects
    void clear();

};

#endif