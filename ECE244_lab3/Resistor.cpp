
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;
#include "Resistor.h"
#include "Rparser.h"


Resistor::Resistor(){}
Resistor :: Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]){
    index= rIndex_;
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[2] = endpoints_[2];
}

Resistor :: ~Resistor() {}


string Resistor::getName ()const{
    return name;
}

double Resistor :: getResistance() const{
    return resistance;
}


int Resistor::getLeftIndex(){
    return endpointNodeIDs[0];
}

int Resistor:: getRightIndex(){
    return endpointNodeIDs[1];
}

void Resistor::setName(string name_){
    name = name_;   
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
}

void Resistor::setNodeConnection(int endpoint[2]){
    endpointNodeIDs[0] = endpoint[0];
    endpointNodeIDs[1] = endpoint[1];
}

void Resistor :: print(){
    cout << name << setfill(' ') << setw(20) << " " << setfill(' ') << setw(7)
    << resistance << setprecision(2) << fixed << " Ohms " << 
     endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] <<endl;
}