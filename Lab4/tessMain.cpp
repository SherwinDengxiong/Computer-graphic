//
//  tessMain.cpp
//
//  Created by Warren R. Carithers 2016/11/04.
//  Based on code created by Joe Geigel and updated by
//    Vasudev Prasad Bethamcherla.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Main program for tessellation assignment.
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

#include "Buffers.h"
#include "ShaderSetup.h"
#include "Canvas.h"
#include "Shapes.h"

using namespace std;

// The shapes that we can draw
#define CUBE 0
#define CYLINDER 1
#define CONE 2
#define SPHERE 3

int currentShape = CUBE;

// dimensions of the drawing window
int w_width  = 512;
int w_height = 512;

// subdivisions for tessellation
int division1 = 1;
int division2 = 1;

// are we animating?
bool animating = false;

// do we need to do a display() call?
bool updateDisplay = true;

// how to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// our Canvas
Canvas *canvas;

// buffer information
BufferSet shapeBuffers;

// GLSL shader program handle
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

// shader arguments
GLuint theta;      // theta uniform location
GLuint vPosition;  // vertex location

// rotation control
float anglesReset[3] = {30.0, 30.0, 0.0};
float angles[3] = {30.0, 30.0, 0.0};
float angleInc = 5.0;

///
// create a new shape by tesselating one of
// the 4 basic objects
///
void createNewShape( void ) {

    // clear the old shape
    canvas->clear();

    // create the new shape
    switch( currentShape )
    {
        case CUBE:
	    makeCube( *canvas, division1 );
	    break;
        case CYLINDER:
	    makeCylinder( *canvas, 0.5, division1, division2 );
	    break;
        case CONE:
	    makeCone( *canvas, 0.5, division1, division2 );
	    break;
        case SPHERE:
	    makeSphere( *canvas, 0.5, division1, division2 );
	    break;
    }

    // create our buffers
    shapeBuffers.createBuffers( *canvas );
}

///
// OpenGL initialization
///
void init( void ) {

    // Create our Canvas
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
        cerr << "Error setting up shaders - " <<
	    errorString(error) << endl;
	glfwTerminate();
	exit( 1 );
    }
    
    // select this shader program
    glUseProgram( program );

    // get location of shader global variables
    vPosition = glGetAttribLocation( program, "vPosition" );
    theta = glGetUniformLocation( program, "theta" );

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glCullFace( GL_BACK );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glClearDepth( 1.0 );

    // initally create a cube
    createNewShape();
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
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // send down our rotation angles
    glUniform3fv( theta, 1, angles );
}

void display( void ) {

    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // bind our buffers
    selectBuffers( program, shapeBuffers );

    // draw our shape
    glDrawElements( GL_TRIANGLES, shapeBuffers.numElements,
                    GL_UNSIGNED_INT, (void *)0 );
}

// Can cause gimbal lock which also happened on Apollo 11
// http://en.wikipedia.org/wiki/Gimbal_lock#Gimbal_lock_on_Apollo_11
// Solution? Use Quaternions (Taught in Comp. Animation: Algorithms)
//
// TIDBIT:
// Quaternion plaque on Brougham (Broom) Bridge, Dublin, which says:
// 
//    "Here as he walked by
//    on the 16th of October 1843
// 
//    Sir William Rowan Hamilton 
//    
//    in a flash of genius discovered
//    the fundamental formula for
//    quaternion multiplication
//    i^2 = j^2 = k^2 = ijk = -1
//    & cut it on a stone of this bridge"

void animate() {
    int i;
    static int level = 0;

    if( level >= 450 ) {
        level = 0;
	animating = false;
    }

    if( !animating ) {
        return;
    }

    if( level < 150 ) {
        angles[0] -= angleInc / 3;
    } else if( level < 300 ) {
        angles[1] -= angleInc / 3;
    } else {
        angles[2] -= angleInc / 3;
    }

    ++level;
    updateDisplay = true;
}


void keyboard( GLFWwindow *window, unsigned int codepoint )
{

    switch( codepoint & 0x7f ) {

	// termination
        case 033:  // Escape key
        case 'q': case 'Q':
            glfwSetWindowShouldClose( window, 1 );

	// automated animation
        case 'a': case 'A':
	    animating = true;
	    break;

	// incremental rotation along the axes
        case 'x': angles[0] -= angleInc; break;
        case 'y': angles[1] -= angleInc; break;
        case 'z': angles[2] -= angleInc; break;
        case 'X': angles[0] += angleInc; break;
        case 'Y': angles[1] += angleInc; break;
        case 'Z': angles[2] += angleInc; break;

	// shape selection
        case '1':  case 'c': currentShape = CUBE; createNewShape(); break;
        case '2':  case 'C': currentShape = CYLINDER; createNewShape(); break;
        case '3':  case 'n': currentShape = CONE; createNewShape(); break;
        case '4':  case 's': currentShape = SPHERE; createNewShape(); break;

	// tessellation factors
        case '+': division1++; createNewShape(); break;
        case '=': division2++; createNewShape(); break;
        case '-': if( division1 > 1 ) {
                    division1--;
                    createNewShape();
		  }
		  break;
        case '_': if( division2 > 1)  {
                    division2--;
                    if (currentShape != CUBE) createNewShape();
                  }
                  break;

	// reset
	case 'r': case 'R':
	    angles[0] = anglesReset[0];
	    angles[1] = anglesReset[1];
	    angles[2] = anglesReset[2];
	    break;
    }

    updateDisplay = true;
}


void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}


///
// main program for tessellation assignment
///
int main( int argc, char **argv ) {

    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 4 - Tessellation", NULL, NULL );

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
    if( !GLEW_VERSION_3_2 ) {
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

    glfwSetCharCallback( window, keyboard );

    while( !glfwWindowShouldClose(window) ) {
        animate();
        if( updateDisplay ) {
            updateDisplay = false;
            display();
            glfwSwapBuffers( window );
        }
        glfwPollEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
