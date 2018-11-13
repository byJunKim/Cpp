/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: kimbyeo4
 *
 * Created on November 30, 2017, 5:15 PM
 */

#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "easygl.h"
#include <iostream>

using namespace std;

class Circle : public Shape {

private:
    float radius;
    float xcen;
    float ycen;
    
public:
Circle(string, string, float, float, float);
Circle(const Circle& orig);
virtual ~Circle();

   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;




};

#endif /* CIRCLE_H */

