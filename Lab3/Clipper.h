//
//  clipper.h
//
//  Created by Warren R. Carithers on 02/27/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "Vertex.h"
#include <iostream>
using namespace std;

///
// Simple module that performs clipping
///

class Clipper {

public:

    ///
    // Constructor
    ///
    Clipper();

    ///
    // clipPolygon
    //
    // Clip the polygon with vertex count in and vertices inV against the
    // rectangular clipping region specified by lower-left corner ll and
    // upper-right corner ur. The resulting vertices are placed in outV.
    //
    // The routine should return the with the vertex count of polygon
    // resulting from the clipping.
    //
    // @param in    the number of vertices in the polygon to be clipped
    // @param inV   the incoming vertex list
    // @param outV  the outgoing vertex list
    // @param ll    the lower-left corner of the clipping rectangle
    // @param ur    the upper-right corner of the clipping rectangle
    //
    // @return number of vertices in the polygon resulting after clipping
    //
    ///
    int clipPolygon( int in, const Vertex inV[], Vertex outV[],
		     Vertex ll, Vertex ur );
    bool isinside(Vertex v, Vertex ll, Vertex ur);
    Vertex findjunction(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur);
    bool arraycontain(const Vertex inV[], Vertex temp,int count);
    bool outsideclip(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur);
    Vertex whichconer(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur,int n);


};

#endif
