//
//  Rasterizer.h
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

class Canvas;

///
// Simple class that performs rasterization algorithms
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
    // @param C The Canvas to use
    ///
    Rasterizer( int n, Canvas &canvas );
    
    ///
    // Draw a filled polygon
    //
    // Implementation should use the scan-line polygon fill algorithm
    // discussed in class.
    //
    // The polygon has n distinct vertices.  The coordinates of the vertices
    // making up the polygon are stored in the x and y arrays.  The ith
    // vertex will have coordinate (x[i],y[i]).
    //
    // You are to add the implementation here using only calls to the
    // setPixel() method of the canvas.
    //
    // @param n - number of vertices
    // @param x - array of x coordinates
    // @param y - array of y coordinates
    ///
    void drawPolygon( int n, const int x[], const int y[] );
    
};


#endif
