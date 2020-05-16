//
//  clipMain.cpp
//
//  Created by Warren R. Carithers on 02/27/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "ShaderSetup.h"
#include "Vertex.h"
#include "Buffers.h"
#include "Canvas.h"
#include "Clipper.h"

using namespace std;

///
// Object information
///

// our clipping regions (ll and ur corners)

Vertex clip1[2] = { {  10, 110 }, {  50, 150 } };
Vertex clip2[2] = { {  30,  10 }, {  70,  80 } };
Vertex clip3[2] = { {  90,  34 }, { 120,  60 } };
Vertex clip4[2] = { {  90,  80 }, { 130, 110 } };
Vertex clip5[2] = { { 198, 198 }, { 276, 258 } };
Vertex clip6[2] = { { 221,  80 }, { 251, 101 } };

// our polygons (list of vertices)

Vertex quad1[] = {
    { 20, 120 }, { 20, 140 }, { 40, 140 }, { 40, 120 }
};
int quad1_nv = sizeof(quad1) / sizeof(Vertex);

Vertex quad2[] = {
    { 80, 160 }, { 80, 200 }, { 60, 200 }, { 60, 160 }
};
int quad2_nv = sizeof(quad2) / sizeof(Vertex);

Vertex quad3[] = {
    { 20, 60 }, { 50, 60 }, { 50, 50 }, { 20, 50 }
};
int quad3_nv = sizeof(quad3) / sizeof(Vertex);

Vertex quad4[] = {
    { 44, 122 }, { 60, 122 }, { 60, 146 }, { 44, 146 }
};
int quad4_nv = sizeof(quad3) / sizeof(Vertex);

Vertex pent1[] = {
    { 80, 20 }, { 90, 10 }, { 110, 20 }, { 100, 50 }, { 80, 40 }
};
int pent1_nv = sizeof(pent1) / sizeof(Vertex);

Vertex hept1[] = {
    { 120, 70 }, { 140, 70 }, { 160, 80 }, { 160, 100 },
    { 140, 110 }, { 120, 100 }, { 110, 90 }
};
int hept1_nv = sizeof(hept1) / sizeof(Vertex);

Vertex nona1[] = {
    { 190,  56 }, { 230,  68 }, { 247,  56 }, { 269,  71 }, { 284, 104 },
    { 251, 122 }, { 233, 110 }, { 212, 119 }, { 203,  95 }
};
int nona1_nv = sizeof(nona1) / sizeof(Vertex);

Vertex deca1[] = {
    { 177, 156 }, { 222, 188 }, { 267, 156 }, { 250, 207 }, { 294, 240 },
    { 240, 240 }, { 222, 294 }, { 204, 240 }, { 150, 240 }, { 194, 207 }
};
int deca1_nv = sizeof(deca1) / sizeof(Vertex);

// count of vertices in each clipped polygon
int nv[8];

///
// Drawing-related variables
///

// dimensions of the drawing window
int w_width  = 300;
int w_height = 300;

// how to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i)        ((char *)NULL + (i))

// our Canvas
Canvas *canvas;

// our Clipper
Clipper clipper;

// variables related to drawing the clipping regions
BufferSet clipBuffers;

// variables related to drawing the original polygons
BufferSet polyOutlineBuffers;

// variables related to drawing the resulting polygons
BufferSet clippedPolyBuffers;

// shader program handle
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

///
// Support function that draws clip regions as line loops
///
void drawClipRegion( Vertex ll, Vertex ur, Canvas &C ) {
    C.setPixel( ll.x, ll.y );  // LL
    C.setPixel( ur.x, ll.y );  // LR
    C.setPixel( ur.x, ur.y );  // UR
    C.setPixel( ll.x, ur.y );  // UL
}

///
// Draw all the clipping rectangles
///
void makeClipOutlines( Canvas &C ) {

    // we draw the clipping regions as white rectangles.
    // all vertices are put into one vertex buffer, and
    // we use glDrawArrays() instead of glDrawElements()
    // to draw them as line loops

    drawClipRegion( clip1[0], clip1[1], C );
    drawClipRegion( clip2[0], clip2[1], C );
    drawClipRegion( clip3[0], clip3[1], C );
    drawClipRegion( clip4[0], clip4[1], C );
    drawClipRegion( clip5[0], clip5[1], C );
    drawClipRegion( clip6[0], clip6[1], C );
}

///
// Draw a polygon
///
void drawPolygon( Vertex v[], int nv, Canvas &C ) {

    // just put the vertices into the vertex buffer, in order

    for( int i = 0; i < nv; ++i ) {
        C.setPixel( v[i].x, v[i].y );
    }
}

///
// Create the polygon outlines
///
void makePolygonOutlines( Canvas &C ) {

    // here, we draw the original polygons; these
    // will be rendered using line loops

    C.setColor( 1.0f, 0.0f, 0.0f );              // red
    drawPolygon( quad1, quad1_nv, C );
    C.setColor( 0.0f, 1.0f, 0.0f );              // green
    drawPolygon( quad2, quad2_nv, C );
    C.setColor( 0.0f, 0.0f, 1.0f );              // blue
    drawPolygon( quad3, quad3_nv, C );
    C.setColor( 1.0f, 0.0f, 1.0f );              // magenta
    drawPolygon( quad4, quad4_nv, C );
    C.setColor( 1.0f, 0.5f, 1.0f );              // red-greenish-blue
    drawPolygon( pent1, pent1_nv, C );
    C.setColor( 0.7f, 0.7f, 0.7f );              // gray
    drawPolygon( hept1, hept1_nv, C );
    C.setColor( 0.871f, 0.722f, 0.529f ); // burlywood
    drawPolygon( nona1, nona1_nv, C );
    C.setColor( 1.0f, 0.64705f, 0.0f );   // orange
    drawPolygon( deca1, deca1_nv, C );
}

///
// Create the filled polygons
///
void makePolygons( Canvas &C ) {
    // temporary vertex array
    Vertex tmp[50];
    int wl;

    ///
    // first polygon:  entirely within region
    ///

    C.setColor( 1.0f, 0.0f, 0.0f );	// red
    wl = 0;
    wl = clipper.clipPolygon( 4, quad1, tmp, clip1[0], clip1[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[0] = wl;
    }

    ///
    // second polygon:  entirely outside region
    ///

    C.setColor( 0.0f, 1.0f, 0.0f ); // green
    wl = 0;
    wl = clipper.clipPolygon( 4, quad2, tmp, clip1[0], clip1[1] );
    // shouldn't draw anything!
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[1] = wl;
    }

    ///
    // third polygon:  halfway outside on left
    ///

    C.setColor( 0.0f, 0.0f, 1.0f );	// blue
    wl = 0;
    wl = clipper.clipPolygon( 4, quad3, tmp, clip2[0], clip2[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[2] = wl;
    }

    ///
    // fourth polygon:  part outside on right
    ///

    C.setColor( 1.0f, 0.0f, 1.0f );	// magenta
    wl = 0;
    wl = clipper.clipPolygon( 4, quad4, tmp, clip1[0], clip1[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[3] = wl;
    }

    ///
    // fifth polygon:  outside on left and bottom
    ///

    C.setColor( 1.0f, 0.5f, 1.0f ); // red-greenish-blue
    wl = 0;
    wl = clipper.clipPolygon( 5, pent1, tmp, clip3[0], clip3[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[4] = wl;
    }

    ///
    // sixth polygon:  outside on top, right, and bottom
    ///

    C.setColor( 0.7f, 0.7f, 0.7f );	// gray
    wl = 0;
    wl = clipper.clipPolygon( 7, hept1, tmp, clip4[0], clip4[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
	nv[5] = wl;
    }

    ///
    // seventh polygon:  surrounds the clip region
    ///

    C.setColor( 0.871f, 0.722f, 0.529f ); // burlywood
    wl = 0;
    wl = clipper.clipPolygon( nona1_nv, nona1, tmp, clip6[0], clip6[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
        nv[6] = wl;
    }

    ///
    // eighth polygon:  outside on all four edges
    ///

    C.setColor( 1.0f, 0.64705f, 0.0f );  // orange
    wl = 0;
    wl = clipper.clipPolygon( deca1_nv, deca1, tmp, clip5[0], clip5[1] );
    if( wl > 0 ) {
        drawPolygon( tmp, wl, C );
        nv[7] = wl;
    }

}

///
// Create all our objects
///
void createImage( void )
{
    // start with a clean canvas
    canvas->clear();

    // first, create the clipping region buffers
    //
    // start by putting all the vertices for all
    // the regions into a single set of buffers

    // draw all of them in white
    canvas->setColor( 1.0f, 1.0f, 1.0f );
    makeClipOutlines( *canvas );

    // collect the vertex, element, and color data for these
    clipBuffers.createBuffers( *canvas );

    // next, do the polygon outlines
    canvas->clear();
    makePolygonOutlines( *canvas );
    polyOutlineBuffers.createBuffers( *canvas );

    // finally, do the polygons
    canvas->clear();
    makePolygons( *canvas );
    clippedPolyBuffers.createBuffers( *canvas );

}

///
// OpenGL initialization
///
void init( void )
{
    // Create our Canvas "object"
    canvas = new Canvas( w_width, w_height );

    if( canvas == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
        glfwTerminate();
        exit( 1 );
    }

    // Load shaders and use the resulting shader program
    ShaderError error;
    if( useAltShaders ) {
        program = shaderSetup( "alt.vert", "alt.frag", &error );
    } else { 
        program = shaderSetup( "shader.vert", "shader.frag", &error );
    }
    if( !program ) {
        cerr << "Error setting up shaders - " << errorString(error) << endl;
	glfwTerminate();
	exit( 1 );
    }

    // OpenGL state initialization
    glEnable( GL_DEPTH_TEST );
    // glEnable( GL_CULL_FACE );
    // glCullFace( GL_BACK );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0f );

    // create the geometry for our shapes.
    createImage();
}

///
// selectBuffers() - bind the correct vertex and element buffers
//
// @param program - GLSL program object
// @param B       - the BufferSet to update
///
void selectBuffers( GLuint program, BufferSet &B ) {

    // bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, B.vbuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, B.ebuffer );

    // set up the vertex attribute variables
    GLuint vPosition = glGetAttribLocation( program , "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(B.vSize) );
}

extern "C" {

void display( void )
{
    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // ensure we have selected the correct shader program
    glUseProgram( program );

    // set up our scale factors for normalization
    GLuint sf = glGetUniformLocation( program, "sf" );
    glUniform2f( sf, 2.0f / (w_width - 1.0f), 2.0f / (w_height - 1.0f) );

    ///
    // first, draw the clip region outlines
    ///

    // bind our buffers
    selectBuffers( program, clipBuffers );

    // draw our shapes
    glDrawArrays( GL_LINE_LOOP,  0, 4 );
    glDrawArrays( GL_LINE_LOOP,  4, 4 );
    glDrawArrays( GL_LINE_LOOP,  8, 4 );
    glDrawArrays( GL_LINE_LOOP, 12, 4 );
    glDrawArrays( GL_LINE_LOOP, 16, 4 );
    glDrawArrays( GL_LINE_LOOP, 20, 4 );

    ///
    // next, draw the polygon outlines
    ///

    // bind our buffers
    selectBuffers( program, polyOutlineBuffers );

    // draw our shapes
    int skip = 0;
    glDrawArrays( GL_LINE_LOOP, skip, quad1_nv ); skip += quad1_nv;
    glDrawArrays( GL_LINE_LOOP, skip, quad2_nv ); skip += quad2_nv;
    glDrawArrays( GL_LINE_LOOP, skip, quad3_nv ); skip += quad3_nv;
    glDrawArrays( GL_LINE_LOOP, skip, quad4_nv ); skip += quad4_nv;
    glDrawArrays( GL_LINE_LOOP, skip, pent1_nv ); skip += pent1_nv;
    glDrawArrays( GL_LINE_LOOP, skip, hept1_nv ); skip += hept1_nv;
    glDrawArrays( GL_LINE_LOOP, skip, nona1_nv ); skip += nona1_nv;
    glDrawArrays( GL_LINE_LOOP, skip, deca1_nv ); skip += deca1_nv;

    ///
    // finally, draw the clipped polygons
    ///

    // bind our buffers
    selectBuffers( program, clippedPolyBuffers );

    // draw our shapes
    //
    // be sure to only draw what's there
    skip = 0;
    if( nv[0] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[0] ); skip += nv[0];
    }
    if( nv[1] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[1] ); skip += nv[1];
    }
    if( nv[2] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[2] ); skip += nv[2];
    }
    if( nv[3] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[3] ); skip += nv[3];
    }
    if( nv[4] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[4] ); skip += nv[4];
    }
    if( nv[5] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[5] ); skip += nv[5];
    }
    if( nv[6] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[6] ); skip += nv[6];
    }
    if( nv[7] ) {
        glDrawArrays( GL_TRIANGLE_FAN, skip, nv[7] ); skip += nv[7];
    }
}

void keyboard( GLFWwindow *window, int key, int scan, int action, int modes )
{
    switch( key ) {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose( window, 1 );
            break;
    }
}

} // extern "C"


void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}


///
// main program for polygon clip assignment
///
int main( int argc, char *argv[] )
{
    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 3 - Polygon Clipping", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: " << glewGetErrorString(err) << endl;
        glfwTerminate();
        exit( 1 );
    }
    if( ! GLEW_VERSION_3_2 ) {
        cerr << "GLEW: OpenGL 3.2 not available" << endl;
        if( !GLEW_VERSION_2_1 ) {
	    cerr << "GLEW: OpenGL 2.1 not available, either!" << endl;
            glfwTerminate();
            exit( 1 );
        }
    }
#endif

    // determine whether or not we can use GLSL 1.50
    int maj = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MAJOR );
    int min = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MINOR );

    cerr << "GLFW: using " << maj << "." << min << " context" << endl;
    if( maj < 3 || (maj == 3 && min < 2) ) {
        // nope!
        useAltShaders = true;
    }

    init();

    glfwSetKeyCallback( window, keyboard );

    while( !glfwWindowShouldClose(window) ) {
        display();
        glfwSwapBuffers( window );
        glfwWaitEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
