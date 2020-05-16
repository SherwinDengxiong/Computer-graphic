//
//  Canvas.cpp
//
//  Created by Warren R. Carithers 2016/09/30.
//  Based on a C++ version created by Joe Geigel.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Routines for adding points to create a new mesh.
//
//  This file should not be modified by students.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>

// Canvas.h includes all the OpenGL/GLFW/etc. header files for us
#include "Canvas.h"

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

Canvas::Canvas( int w, int h ) : width(w), height(h) {
    currentColor[0] = 0.0f;
    currentColor[1] = 0.0f;
    currentColor[2] = 0.0f;
    pointArray = 0;
    colorArray = 0;
    elemArray = 0;
    numElements = 0;
}


///
// Destructor
///

Canvas::~Canvas( void ) {
    clear();
}


///
// clear the canvas
///
void Canvas::clear( void )
{
    if( pointArray ) {
        delete [] pointArray;
        pointArray = 0;
    }
    if( elemArray ) {
        delete [] elemArray;
        elemArray = 0;
    }
    if( colorArray ) {
        delete [] colorArray;
        colorArray = 0;
    }
    points.clear();
    colors.clear();
    numElements = 0;
    currentColor[0] = 0.0f;
    currentColor[1] = 0.0f;
    currentColor[2] = 0.0f;
}


///
// change the current drawing color
//
// @param r The red component of the new color (between 0-1)
// @param g The green component of the new color (between 0-1)
// @param b The blue component of the new color (between 0-1);
///
void Canvas::setColor( float r, float g, float b )
{
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
}


///
// set a pixel to the current drawing color
//
// @param x The x coord of the pixel to be set
// @param y The y coord of the pixel to be set
///
void Canvas::setPixel( int x0, int y0 )
{
    points.push_back( (float) x0 );
    points.push_back( (float) y0 );
    points.push_back( -1.0f );  // fixed Z depth
    points.push_back( 1.0f );

    colors.push_back( currentColor[0] );
    colors.push_back( currentColor[1] );
    colors.push_back( currentColor[2] );
    colors.push_back( 1.0f );   // alpha channel

    numElements += 1;
}


///
// gets the array of vertices for the current shape
///
float *Canvas::getVertices( void )
{
    int i;

    // delete the old point array if we have one
    if( pointArray ) {
        delete [] pointArray;
    }

    // create and fill a new point array
    pointArray = new float[ points.size() ];
    if( pointArray == 0 ) {
    	cerr << "point allocation failure" << endl;
	exit( 1 );
    }
    for( i = 0; i < points.size(); i++ ) {
        pointArray[i] = points[i];
    }

    return pointArray;
}


///
// gets the array of elements for the current shape
///
GLuint *Canvas::getElements( void )
{
    int i;

    // delete the old element array if we have one
    if( elemArray ) {
        delete [] elemArray;
    }

    // create and fill a new element array
    elemArray = new GLuint[ points.size() ];
    if( elemArray == 0 ) {
    	cerr << "element allocation failure" << endl;
	exit( 1 );
    }
    for( i = 0; i < points.size(); i++ ) {
        elemArray[i] = i;
    }

    return elemArray;
}


///
// gets the array of colors for the current shape
///
float *Canvas::getColors( void )
{
    int i;

    // delete the old color array if we have one
    if( colorArray ) {
        delete [] colorArray;
    }

    // create and fill a new color array
    colorArray = new float[ colors.size() ];
    if( colorArray == 0 ) {
    	cerr << "color allocation failure" << endl;
	exit( 1 );
    }
    for( i = 0; i < colors.size(); i++ ) {
        colorArray[i] = colors[i];
    }

    return colorArray;
}


///
// returns number of vertices in current shape
///
int Canvas::numVertices( void )
{
    return numElements;
}
