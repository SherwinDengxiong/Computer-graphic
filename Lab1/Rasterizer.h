//
//  Rasterizer.h
//
//  Created by Warren R. Carithers on 01/27/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "Canvas.h"

///
// Simple structure that performs rasterization
///

class Rasterizer {

    ///
    // number of scanlines
    ///

    int n_scanlines;

public:
    ///
    // Drawing canvas
    ///

    Canvas &C;

    ///
    // Constructor
    //
    // @param n number of scanlines
    // @param C drawing canvas to use
    ///

    Rasterizer( int n, Canvas &canvas );

    ///
    // Draw my initials
    //
    // Draw my own initials using calls to drawLine(), in the same
    // manner that makeLines() in the driver program draws 'GO'.
    //
    ///

    void myInitials( void );

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

    void drawLine(int x0, int y0, int x1, int y1 );

};

#endif
