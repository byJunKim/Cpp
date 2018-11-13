/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.cpp
 * Author: kimbyeo4
 * 
 * Created on November 30, 2017, 5:50 PM
 */

#include "Polygon.h"

Polygon::Polygon(string _name, string _colour, float _xcen, float _ycen, t_point _vertices[], int _nPoint) :Shape(_name, _colour, _xcen, _ycen) {
    
    nPoint = _nPoint;
    
    for(int i=0; i<nPoint; i++){
        vertices[i].x = _vertices[i].x;
        vertices[i].y = _vertices[i].y;
    }
            
    
}


Polygon::~Polygon() {
}



void Polygon::print () const {
   Shape::print();
   cout << "polygon";
   
   for(int i=0; i< nPoint; i++){
       cout << " (" << vertices[i].x + getXcen() << "," << vertices[i].y + getYcen() << ")" ;
   }
   cout << endl; 
}


void Polygon::scale (float scaleFac) {
   
    for(int i=0; i< nPoint; i++){
        vertices[i].x = scaleFac*vertices[i].x;
        vertices[i].y = scaleFac*vertices[i].y;
    }
   
   
}
   

float Polygon::computeArea () const {
     float area = 0;         // Accumulates area in the loop
  int j = nPoint-1;  // The last vertex is the 'previous' one to the first

  for (int i=0; i<nPoint; i++)
    { area = area +  (vertices[j].x+vertices[i].x) * (vertices[j].y-vertices[i].y); 
      j = i;  //j is previous vertex to i
    }
  return area/2;
}


float Polygon::computePerimeter () const {
   float perimeter = 0;
   t_point vec;
   int endIndex;
    for(int i=0; i<nPoint; i++){
        endIndex = (i + 1) % nPoint;
        vec = getVecBetweenPoints(vertices[i], vertices[endIndex]);
        perimeter = perimeter + sqrt((vec.x)*(vec.x)+(vec.y)*(vec.y));
    }
   return perimeter;
}


void Polygon::draw (easygl* window) const {
   
    t_point verticeCopy[100];
    for(int i=0; i<nPoint; i++){
        verticeCopy[i].x = vertices[i].x+getXcen();
        verticeCopy[i].y = vertices[i].y+getYcen();
    }
   
   window->gl_setcolor(getColour());
   window->gl_fillpoly(verticeCopy, nPoint);
}


bool Polygon::pointInside (float x, float y) const {
    
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   

   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < nPoint; istart++) {
      endIndex = (istart + 1) % nPoint; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (vertices[istart], vertices[endIndex]);
      yDistance = (click.y - vertices[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }

      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = vertices[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   return (sidesToLeft == 1);

}




t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}
