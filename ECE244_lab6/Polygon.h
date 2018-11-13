/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: kimbyeo4
 *
 * Created on November 30, 2017, 5:50 PM
 */

#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include "Shape.h"
#include "easygl.h"
#include "easygl_constants.h"
#include <math.h>

using namespace std;

class Polygon : public Shape {

private:
    t_point vertices[100];
    int nPoint;
    t_point getVecBetweenPoints (t_point start, t_point end) const;

    
public:
Polygon(string, string, float, float, t_point[], int);

virtual ~Polygon();

   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window)const;
   virtual bool pointInside (float x, float y) const;
   
   
   



};

#endif /* POLYGON_H */

