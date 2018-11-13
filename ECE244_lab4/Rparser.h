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
#include "ResistorList.h"
#include "NodeList.h"

//Jun y are u so smart?
//i broke ur code so goodluck have fun finding it

//int parser(int &maxNodeNumber, int &maxResistors);
void insertR(stringstream &lineStream, bool &err, NodeList &Nptr);
void modifyR(stringstream & lineStream, bool &err, NodeList &Nptr);
void deleteR(stringstream &lineStream, bool &err, NodeList &Nptr);
void printNode(stringstream &lineStream, NodeList &Nptr);
void printR(stringstream &lineStream, NodeList &Nptr);
void setV(stringstream & lineStream, bool &err, NodeList & Nptr);
void unsetV(stringstream & lineStream, bool &err, NodeList & Nptr);
void solve(stringstream &lineStream, bool &err, NodeList &Nptr);
void printInvalidArg(stringstream &lineStream);
bool isItNumber(stringstream &lineStream);
bool isItNegative(stringstream &lineStream);
bool isItPositive(stringstream &lineStream);
bool findResName(string &name);
void printAll(string name);


#endif /* RPARSER_H */



