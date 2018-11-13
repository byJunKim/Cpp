/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.cpp
 * Author: kimbyeo4
 * 
 * Created on November 29, 2017, 6:11 PM
 */

#include "Rectangle.h"

Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height) : Shape(_name, _colour, _xcen, _ycen){

    width = _width;
    height = _height;
}

Rectangle::Rectangle(const Rectangle& orig) {
}

Rectangle::~Rectangle() {
}


void Rectangle::print () const {
   Shape::print();
   cout << "rectangle";
   cout <<  " width: " << width << " height: " << height << endl; 
}


void Rectangle::scale (float scaleFac) {
   width = scaleFac*width;
   height = scaleFac*height;
   
   
}
   

float Rectangle::computeArea () const {
    float area;
   area = width * height; 
   return area;
}


float Rectangle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2*(width+height); 
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
   
   window->gl_setcolor(getColour());
   window->gl_fillrect((getXcen() - width/2), (getYcen() - height/2), (getXcen() + width/2), (getYcen() + height/2));
}


bool Rectangle::pointInside (float x, float y) const {
    
    if(((x >= getXcen() - width/2) && x <= (getXcen() + width/2)) && ((y >= getYcen() - height/2) & (y <= getYcen() + height/2) )){
    //    setXcen(x);
      //  setYcen(y);
        return true;
    }
    else return false;

}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
