


#ifndef RESISTOR_H
#define RESISTOR_H

class Resistor {
private:
    double resistance = 0.0; // resistance (in Ohms)
    string name = "empty"; // name is initialized to "empty"
    int endpointNodeIDs[2] = {-1, -1}; // IDs of nodes it attaches to
    int index = -1; //index of resistor is initialized to -1
public:

    Resistor();

    Resistor(int rIndex_, string name_, double resistance_, int endpoints_[2]);
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects

    ~Resistor(); //destructor

    string getName() const; // returns the name
    
    double getResistance() const; // returns the resistance


    int getLeftIndex();
    int getRightIndex();

    //sets the resistor name to the private string name
    void setName(string name_);
    
    //set the resistance to the private double resistance
    void setResistance(double resistance_);
    
    //set the two ends of the node to the private integer array endpointNodeIDs
    void setNodeConnection(int endpoint[2]);

    //prints the specific resistor information
    void print();
};

ostream& operator<<(ostream&, const Resistor&);

#endif /* RESISTOR_H */

