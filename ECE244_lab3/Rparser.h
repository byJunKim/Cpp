/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: kimbyeo4
 *
 * Created on October 16, 2017, 5:38 PM
 */

#ifndef RPARSER_H
#define RPARSER_H
#include "Node.h"
#include "Resistor.h"

//int parser(int &maxNodeNumber, int &maxResistors);
void insertR(stringstream &lineStream, int &maxNodeNumber, int &maxResistors, int rIndex, bool &err);
void modifyR(stringstream & lineStream, int &maxResistors, bool &err , int &rIndex);
void deleteR(stringstream &lineStream, bool err, int &rIndex, int &maxNodeNumber, int&maxResistors);
void printNode(stringstream &lineStream, int &maxNodeNumber);
void printR(stringstream &lineStream, int &maxResistors, int &rIndex);
void printInvalidArg(stringstream &lineStream);
bool isItNumber(stringstream &lineStream);
bool isItNegative(stringstream &lineStream);
bool isItPositive(stringstream &lineStream);
void setMaxVal(stringstream &lineStream, int &maxNodeNumbers, int &maxResistors, int &rIndex, bool &err);
bool findResName( int &maxResistors, int &rIndex, string &name);
void printAll( int &rIndex, string name);


#endif /* RPARSER_H */



