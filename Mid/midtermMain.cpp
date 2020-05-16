//
//  midtermMain.cpp
//
//  Main program for CG 2D Pipeline midterm
//
//  Created by Warren R. Carithers on 2016/10/19.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
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
#include "Pipeline.h"

using namespace std;

///
// some globals since I didn't want to make a midtermMain class.
///

// Which image are we showing?
int displayNumber = 1;

// Polygon IDs for our objects
int triangle;
int square;
int octagon;
int star;
int R;
int I;
int T;
int H;

// Object vertex lists
Vertex triangleVerts[] = {
    { 25.0f, 125.0f }, { 75.0f, 125.0f }, { 50.0f, 175.0f }
};
Vertex squareVerts[] = {
    { 125.0f, 125.0f }, { 175.0f, 125.0f },
    { 175.0f, 175.0f }, { 125.0f, 175.0f }
};
Vertex octagonVerts[] = {
    { 25.0f, 25.0f }, { 35.0f, 15.0f }, { 55.0f, 15.0f }, { 75.0f, 25.0f },
    { 75.0f, 55.0f }, { 55.0f, 75.0f }, { 35.0f, 75.0f }, { 25.0f, 55.0f }
};
Vertex starVerts[] = {
    { 150.0f, 90.0f }, { 140.0f, 65.0f }, { 110.0f, 65.0f }, { 140.0f, 40.0f },
    { 110.0f, 10.0f }, { 150.0f, 25.0f }, { 190.0f, 10.0f }, { 160.0f, 40.0f },
    { 190.0f, 65.0f }, { 160.0f, 65.0f }
};
Vertex rVerts[] = {
    {  10.0f, 480.0f }, { 140.0f, 480.0f }, { 175.0f, 450.0f },
    { 175.0f, 430.0f }, { 140.0f, 370.0f }, {  90.0f, 370.0f },
    { 175.0f, 140.0f }, { 145.0f, 140.0f }, {  65.0f, 370.0f },
    {  35.0f, 370.0f }, {  35.0f, 140.0f }, {  10.0f, 140.0f }
};
Vertex iVerts[] = {
    { 190.0f, 480.0f }, { 340.0f, 480.0f }, { 340.0f, 440.0f },
    { 280.0f, 440.0f }, { 280.0f, 180.0f }, { 340.0f, 180.0f },
    { 340.0f, 140.0f }, { 190.0f, 140.0f }, { 190.0f, 180.0f },
    { 250.0f, 180.0f }, { 250.0f, 440.0f }, { 190.0f, 440.0f }
};
Vertex tVerts[] = {
    { 360.0f, 480.0f }, { 480.0f, 480.0f }, { 480.0f, 440.0f },
    { 430.0f, 440.0f }, { 430.0f, 140.0f }, { 400.0f, 140.0f },
    { 400.0f, 440.0f }, { 360.0f, 440.0f }
};
Vertex hVerts[] = {
    {  35.0f, 450.0f }, { 110.0f, 450.0f }, { 130.0f, 430.0f },
    { 110.0f, 410.0f }, {  35.0f, 410.0f }
};

// Dimensions of the drawing window
int w_width  = 500;
int w_height = 500;

// Our Pipeline
Pipeline *pipeline;

// variables related to drawing the resulting polygons
BufferSet polyBuffers;

// shader program handle
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

bool updateDisplay = true;

///
// Definitions
///

// how to calculate an offset into the vertex buffer
#define	BUFFER_OFFSET(i)	((char *)NULL + (i))

///
// Functions
///

///
// Create all the polygon objects
///

void createPolygons( Pipeline &P )
{
    triangle = P.addPoly( triangleVerts, 3 );
    square   = P.addPoly( squareVerts, 4 );
    octagon  = P.addPoly( octagonVerts, 8 );
    star     = P.addPoly( starVerts, 10 );
    R        = P.addPoly( rVerts, 12 );
    I        = P.addPoly( iVerts, 12 );
    T        = P.addPoly( tVerts, 8 );
    H        = P.addPoly( hVerts, 5 );
}

///
// Draw plain old polygons.
///

void drawPolysNorm( Pipeline *P )
{
    ///
    // Draw a dark blue/purple triangle
    ///
    P->setColor( 0.25f, 0.0f, 0.74f );
    P->drawPoly( triangle );

    ///
    // Draw a green square
    ///
    P->setColor( 0.0f, 0.91f, 0.08f );
    P->drawPoly( square );

    ///
    // Draw a pink octagon
    ///
    P->setColor( 0.98f, 0.0f, 0.48f );
    P->drawPoly( octagon );

    ///
    // Draw a green star
    ///
    P->setColor( 0.68f, 0.0f, 0.75f );
    P->drawPoly( star );
}

///
// Draw the world transformed
///

void drawPolysXform( Pipeline *P ) {

    ///
    // Draw a dark blue/purple triangle rotated
    ///
    P->clearTransform();
    P->rotate( -25.0f );
    P->setColor( 0.25f, 0.0f, 0.74f );
    P->drawPoly( triangle );

    ///
    // Draw a green square translated
    ///
    P->clearTransform();
    P->translate( 80.0f, 75.0f );
    P->setColor( 0.0f, 0.91f, 0.08f );
    P->drawPoly( square );

    ///
    // Draw a pink octagon scaled
    ///
    P->clearTransform();
    P->scale( 0.75f, 0.5f );
    P->setColor( 0.98f, 0.0f, 0.48f );
    P->drawPoly( octagon );

    ///
    // Draw a green star translated, scaled, rotated, then scaled back
    ///
    P->clearTransform();
    P->translate( 50.0f, 50.0f );
    P->scale( 2.0f, 2.0f );
    P->rotate( -10.0f );
    P->translate( -50.0f, 50.0f );
    P->setColor( 0.68f, 0.0f, 0.75f );
    P->drawPoly( star );
}

///
// Draw the RIT letters.
///

void drawLetters( Pipeline *P )
{
    ///
    // Draw with staggered translation
    ///

    P->clearTransform();
    P->translate( 15.0f, 0.0f );
    P->drawPoly( R );

    P->clearTransform();
    P->translate( 10.0f, 0.0f );
    P->drawPoly( I );

    P->clearTransform();
    P->translate( 5.0f, 0.0f );
    P->drawPoly( T );

    P->clearTransform();
    P->translate( 15.0f, 0.0f );
    P->setColor( 0.0f, 0.0f, 0.0f );
    P->drawPoly( H );
}

///
// Draw the objects
///
void drawObjects( Pipeline *P )
{
    ///
    // Set clear color to black
    ///
    P->setColor( 0.0f, 0.0f, 0.0f );
    P->clear();
    P->clearTransform();

    switch( displayNumber % 4 ) {

        case 1: // plain old polygon test

	    // default clip window
            P->setClipWindow( 0.0f, (float)(w_height-1),
	                     0.0f, (float)(w_width-1)   );

            // default viewport
            P->setViewport( 0, 0, w_width, w_height );

            // draw the polys
            drawPolysNorm( P );
            break;
    
        case 2: // clipping test

	    // modified clip window
            P->setClipWindow( 35.0f, 175.0f, 35.0f, 165.0f );

            // default viewport
            P->setViewport( 0, 0, w_width, w_height );

            // draw the polys
            drawPolysNorm( P );
	    break;

        case 3: // varying transformations

            // default clip window
            P->setClipWindow( 0.0f, (float)(w_height-1),
	                     0.0f, (float)(w_width-1)   );

            // default viewport
            P->setViewport( 0, 0, w_width, w_height );

            // draw the transformed polys
            drawPolysXform( P );
	    break;

        case 0: // multiple varying viewports

            // default clipping
            P->setClipWindow( 0.0f, (float)(w_height-1),
	                     0.0f, (float)(w_width-1)   );

            // have some fun with the view port
            int wdiff = w_width / 3;
            int hdiff = w_height / 3;

            // will use xaspect and yaspect to
            // draw each row with a different ratio
            int xaspect = w_width / 3;
            int yaspect = w_height / 3;
            int x = 0;
            int y = 0;
            int i, j;

            for( i = 0; i < 3; i++ ) {
                // adjust yaspect
                yaspect = hdiff/(i+1);

                for( j = 0; j < 3; j++ ) {
                    // let's play around with colors
                    if( i == j ) // 1::1 ratios
                        P->setColor( 0.98f, 0.31f, 0.08f );
                    else if( i < j ) // yaspect is smaller
                        P->setColor( 0.0f, 0.91f, 0.08f );
                    else // i > j, xaspect larger
                        P->setColor( 0.98f, 0.0f, 0.48f );

                    // adjust xaspect and shift to next column
                    xaspect = wdiff/(j+1);
                    P->setViewport( x, y, xaspect, yaspect );
                    drawLetters( P );
                    x += wdiff + 35;
                }

                // shift to next row, also add a little extra space due
                // to aspect ratio stuff making lots of blank canvas
                y += hdiff + 35;

                // change y aspect ratio
                xaspect = wdiff;

                // reset to left side of canvas
                x = 0;
            }
	    break;
    }
}

///
// OpenGL initialization
///
void init( void )
{
    // Create our Pipeline
    pipeline = new Pipeline( w_width, w_height );

    if( pipeline == NULL ) {
        cerr << "error - cannot create Pipeline" << endl;
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
    createPolygons( *pipeline );
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

void display( void )
{
    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // ensure we have selected the correct shader program
    glUseProgram( program );

    // set up our uniforms
    GLuint sf = glGetUniformLocation( program, "sf" );
    glUniform2f( sf, 2.0f / (w_width - 1.0f), 2.0f / (w_height - 1.0f) );

    // draw the objects and create the buffers
    drawObjects( pipeline );
    polyBuffers.createBuffers( pipeline );

    // bind the buffers
    selectBuffers( program, polyBuffers );

    if( pipeline->isOutline() ) {

        // draw the objects as separate line loops

	int skip = 0;
	for( int i = 0; i < pipeline->countNum; ++i ) {
            glDrawArrays( GL_LINE_LOOP, skip, pipeline->outlineCounts[i] );
	    skip += pipeline->outlineCounts[i];
	}

    } else {

	// draw all the individual points
        glDrawElements( GL_POINTS, polyBuffers.numElements,
	                GL_UNSIGNED_INT, 0 );

    }
}

///
// Callback for key presses
///
void keyboard( GLFWwindow *window, int key, int scan, int action, int modes )
{
    switch( key ) {

        case GLFW_KEY_ESCAPE:  // Escape key
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose( window, 1 );
            break;

        case GLFW_KEY_P:  // basic polygons
        case GLFW_KEY_1:
            displayNumber = 1;
            break;

        case GLFW_KEY_C:  // altered clipping
        case GLFW_KEY_2:
            displayNumber = 2;
            break;

        case GLFW_KEY_T:  // object transformations
        case GLFW_KEY_3:
            displayNumber = 3;
            break;

        case GLFW_KEY_V:  // altered viewports
        case GLFW_KEY_4:
            displayNumber = 4;
            break;

	default:   // everything else
	    // return without triggering a redisplay
	    return;

    }

    updateDisplay = true;
}

///
// Callback for mouse button clicks
///
void mouse( GLFWwindow *window, int button, int action, int mods )
{
    if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ) {
        displayNumber++;
        updateDisplay = true;
    }
}

void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}

///
// main program for the 2D pipeline assignment
///
int main( int argc, char *argv[] )
{
    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Project 1 - Midterm", NULL, NULL );

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
    glfwSetMouseButtonCallback( window, mouse );

    while( !glfwWindowShouldClose(window) ) {
	if( updateDisplay ) {
	    updateDisplay = false;
            display();
	}
        glfwSwapBuffers( window );
        glfwWaitEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
