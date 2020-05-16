//
//  Rasterizer.cpp
//
//  Created by Warren R. Carithers on 01/28/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include <cmath>

#include "Rasterizer.h"

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
// @param C the Canvas to be used
///

Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}


///
// Draw my initials
//
// Draw my own initials using calls to drawLine(), in the same
// manner that makeLines() in the driver program draws 'CG'.
///

void Rasterizer::myInitials( void ) {

    // ######## Use light blue (0.678,0.847,0.902) for initials ######## 

    C.setColor( 0.678, 0.847, 0.902 );

    //
    // add code here to draw your initials
    // with calls to your drawLine() function
    //
    drawLine(75,275,150,200);
    drawLine(150,200,225,275);
    drawLine(225,275,250,250);
    drawLine(175,175,250,250);
    drawLine(175,175,250,100);
    drawLine(225,75,250,100);
    drawLine(150,150,225,75);
    drawLine(75,75,150,150);
    drawLine(50,100,75,75);
    drawLine(50,100,125,175);
    drawLine(50,250,125,175);
    drawLine(50,250,75,275);

    C.setColor(100,200,100);
    drawLine(350,275,450,275);
    drawLine(450,275,500,225);
    drawLine(500,225,500,125);
    drawLine(450,75,500,125);
    drawLine(350,75,450,75);
    drawLine(350,75,350,275);
    drawLine(375,250,450,250);
    drawLine(450,250,475,225);
    drawLine(475,225,475,125);
    drawLine(450,100,475,125);
    drawLine(375,100,450,100);
    drawLine(375,100,375,250);

}

///
// Draw a line from (x0,y0) to (x1, y1)
//
// Implementation should be using the Midpoint Line Algorithm.
//
// You are to add the implementation here using only calls to the
// setPixel() method of the Canvas.
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
///

void Rasterizer::drawLine( int x0, int y0, int x1, int y1 )
{
    //
    // add code here to implement drawLine()
    // using the midpoint line algorithm
    //
    int dx,dy;
    int p;
    int x,y;
    if(x1>x0){
        if(y1>=y0){
            dx=x1-x0;
            dy=y1-y0;

            p=2*dy-dx;
            x=x0;
            y=y0;
            C.setPixel(x,y);
            for(int i=0;i<=dx;i++){
                x++;
                if(p<0){
                    p+=2*dy;
                } else{
                    y++;
                    p+=2*(dy-dx);
                }
                C.setPixel(x,y);
            }
        }else{
            dx=x1-x0;
            y1=2*y0-y1;
            dy=y1-y0;
            p=2*dy-dx;
            x=x0;
            y=y0;
            C.setPixel(x,2*y0-y);
            for(int i=0;i<=dx;i++){
                x++;

                if(p<0){
                    p+=2*dy;
                } else{
                    y++;
                    p+=2*(dy-dx);
                }
                C.setPixel(x,2*y0-y);
            }
        }

    } else if(x1<x0){
        if(y1>=y0){
            x1=2*x0-x1;
            dx=x1-x0;
            dy=y1-y0;
            p=2*dy-dx;
            x=x0;
            y=y0;
            C.setPixel(2*x0-x,y);
            for(int i=0;i<=dx;i++){
                x++;
                if(p<0){
                    p+=2*dy;
                } else{
                    y++;
                    p+=2*(dy-dx);
                }
                C.setPixel(2*x0-x,y);
            }
        } else{
            int temp;//switch the x and the y
            temp=x0;
            x0=x1;
            x1=temp;
            temp=y0;
            y0=y1;
            y1=temp;
            dx=x1-x0;
            dy=y1-y0;
            p=-dx;
            x=x0;
            y=y0;
            C.setPixel(x,y);
            for(int i=0;i<=dx;i++){
                x++;
                if(p<0){
                    p+=2*dy;
                } else{
                    y++;
                    p+=2*(dy-dx);
                }
                C.setPixel(x,y);
            }
        }
    }else if(x1=x0){
        if(y1>y0){
            dy=y1-y0;
            x=x0;
            for(int i=0;i<=dy;i++){
                C.setPixel(x,y0+i);
            }
        } else{
            dy=y0-y1;
            x=x0;
            for(int i=0;i<=dy;i++){
                C.setPixel(x,y0-i);
            }
        }
    }

}
