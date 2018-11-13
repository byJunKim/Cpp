/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: kimbyeo4
 *
 * Created on November 29, 2017, 6:11 PM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "easygl.h"
#include <iostream>

using namespace std;

class Rectangle : public Shape {

private:
    float width;
    float height;
    
public:
Rectangle(string, string, float, float, float, float);
Rectangle(const Rectangle& orig);
virtual ~Rectangle();

   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;




};

#endif /* RECTANGLE_H */

