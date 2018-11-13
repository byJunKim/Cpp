/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.cpp
 * Author: kimbyeo4
 * 
 * Created on November 30, 2017, 5:15 PM
 */
#include "Circle.h"

Circle::Circle(string _name, string _colour, float _xcen, float _ycen, float _radius) : Shape(_name, _colour, _xcen, _ycen) {
    radius = _radius;
    xcen = _xcen;
    ycen = _ycen;
}

Circle::Circle(const Circle& orig) {
}

Circle::~Circle() {
}



void Circle::print () const {
   Shape::print();
   cout << "circle";
   cout <<  " radius: " << radius << endl; 
}


void Circle::scale (float scaleFac) {
    radius = scaleFac * radius;
}
   

float Circle::computeArea () const {
    float area;
   area = PI*radius*radius; 
   return area;
}


float Circle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2*PI*radius; 
   return perimeter;
}


void Circle::draw (easygl* window) const {
   
   window->gl_setcolor(getColour());
   window->gl_fillarc (xcen, ycen, radius, 0, 360);
}


bool Circle::pointInside (float x, float y) const {
    if((x-getXcen())*(x-getXcen())+(y-getYcen())*(y-getYcen()) <= radius*radius)
        return true;
    else return false;

}


