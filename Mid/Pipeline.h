//
//  Pipeline.h
//
//  Created by Warren R. Carithers on 2016/10/19.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "Canvas.h"
#include "Vertex.h"
#include <math.h>
#include <vector>


using namespace std;

struct Edge;



///
// Simple wrapper class for midterm assignment
//
// Only methods in the implementation file whose bodies
// contain the comment
//
//    // YOUR IMPLEMENTATION HERE
//
// are to be modified by students.
///

class Pipeline : public Canvas {

public:

    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    Pipeline(int w, int h);
    //store the information of the vertex of the picture in the vertexlist
    vector<vector<Vertex>> vertexlist;
    vector<float> clipinfo;
    //vector<float> viewinfo;
    //parameters

     //   vertexlist   store all the vertex line by line for the plotting
    //    clipinfo    the x y coordinate of the clip window
     //   resultmat   the normalizeand transform matrix

     //   curmat       the changes of the polygon including translate, slope, rotate shown as matrix

     //   polyid     is the id of the polygon

   
    
    vector<vector<float>> resultmat;
    vector<vector<float>> curmat;
    int polyid = 0;
    
    ///
    // addPoly - Add a polygon to the canvas.  This method does not draw
    //           the polygon, but merely stores it for later drawing.
    //           Drawing is initiated by the drawPoly() method.
    //
    // @param p - Array of Vertex entries defining the polygon to be added
    // @param n - Number of vertices in polygon
    //
    // @return a unique integer identifier for the polygon
    ///
    int addPoly( const Vertex p[], int n );

    ///
    // drawPoly - Draw the polygon with the given id.  The polygon should
    //            be drawn after applying the current transformation to
    //            the vertices of the polygon.
    //
    // @param polyID - the ID of the polygon to be drawn.
    ///
    void drawPoly( int polyID );

    ///
    //
    // clearTransform - Set the current transformation to the identity matrix.
    //
    ///
    void clearTransform( void );

    ///
    // translate - Add a translation to the current transformation by
    //             premultiplying the appropriate translation matrix to
    //             the current transformation matrix.
    //
    // @param tx - Amount of translation in x.
    // @param ty - Amount of translation in y.
    //
    ///
    void translate( float tx, float ty );

    ///
    // rotate - Add a rotation to the current transformation by premultiplying
    //          the appropriate rotation matrix to the current transformation
    //          matrix.
    //
    // @param degrees - Amount of rotation in degrees.
    ///
    void rotate( float degrees );

    ///
    // scale - Add a scale to the current transformation by premultiplying
    //         the appropriate scaling matrix to the current transformation
    //         matrix.
    //
    // @param sx - Amount of scaling in x.
    // @param sy - Amount of scaling in y.
    ///
    void scale( float sx, float sy );

    ///
    // setClipWindow - Define the clip window.
    //
    // @param bottom - y coord of bottom edge of clip window (in world coords)
    // @param top - y coord of top edge of clip window (in world coords)
    // @param left - x coord of left edge of clip window (in world coords)
    // @param right - x coord of right edge of clip window (in world coords)
    ///
    void setClipWindow( float bottom, float top, float left, float right );

    ///
    // setViewport - Define the viewport.
    //
    // @param xmin - x coord of lower left of view window (in screen coords)
    // @param ymin - y coord of lower left of view window (in screen coords)
    // @param width - width of view window (in world coords)
    // @param height - width of view window (in world coords)
    ///
    void setViewport( int x, int y, int width, int height );
    //createedgetable is to create an edge table according to the edge information.
    //in the begin, edges will be stored according to its lowest y coordinate.

    vector<vector<Edge>> createedgetable(int xlist[], int ylist[], int length);

    //dothedraw   this method is to use edgetableand scan line by line to fill the polygon
    void dothedraw(vector<vector<Edge>> edgetable, float ymax, float ymin);
    //vectorsort   this method is to sort the edge in the AET according to the x coordinate of lowest y and its slope;
    vector<Edge> vectorsort(vector<Edge> Edgelist);

    //multiply this method is to do the multiply of the matrix.it only used in 3 * 3 matrix;
    vector<vector<float>> multiply(vector<vector<float>> m1, vector<vector<float>> m2);
    
    //clippolygon     this method is to return the vertex after cliping

    vector<Vertex> clipPolygon(vector<Vertex> input, float bottom, float top, float left, float right);

    //is outside    this method is to dicided vertex is outside
    bool isoutside(Vertex point, float bottom, float top, float left, float right);
    //find junction   this method is to find the junction of the cliping edgeand the actual edgeand return the vertex of the junction.
    Vertex findjunctioin(Vertex outside, Vertex inside, float edge,int edgeindex);
    Edge findsmalledge(vector<Edge> edgelist);
   
    

};

#endif
