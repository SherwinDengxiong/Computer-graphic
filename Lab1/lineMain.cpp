//
//  lineMain.cpp
//
//  Main program for line drawing assignment
//
//  Students should not be modifying this file.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>

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
#include "Rasterizer.h"

using namespace std;

// dimensions of drawing window

int w_width  = 600;
int w_height = 600;

// how to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i)	((char *)NULL + (i))

// Our Rasterizer
Rasterizer *rasterizer;

// buffer information
BufferSet shapes;

// shader program ID
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

//
// draw all the lines
//
// Idea for lettering style from:
// http://patorjk.com/software/taag/#p=display&f=Star%20Wars&t=Type%20Something
//          _______   ______   
//         /  ____|  /  __  \
//        |  |  __  |  |  |  | 
//        |  | |_ | |  |  |  | 
//        |  |__| | |  `--'  | 
//         \______|  \______/
//
void makeLines( Rasterizer &R )
{
    // start with a clean canvas
    R.C.clear();

    // ######## The letter 'G' in green ########

    R.C.setColor( 0.0, 1.0, 0.0 );


    R.drawLine(  80, 340, 220, 340 );  // Horizontal left to right
    R.drawLine(  40, 380,  80, 340 );  // 315 degree slope
    R.drawLine( 220, 340, 260, 380 );  // 45 degree slope
    R.drawLine( 260, 380, 260, 440 );  // Vertical bottom to top
    R.drawLine( 260, 440, 180, 440 );  // Horizontal right to left
    R.drawLine( 180, 440, 180, 400 );
    R.drawLine( 180, 400, 220, 400 );
    R.drawLine( 220, 400, 200, 380 );
    R.drawLine( 200, 380, 100, 380 );
    R.drawLine( 100, 380,  80, 400 );
    R.drawLine(  80, 400,  80, 500 );
    R.drawLine(  80, 500, 100, 520 );
    R.drawLine( 100, 520, 200, 520 );
    R.drawLine( 200, 520, 220, 500 );
    R.drawLine( 220, 500, 220, 480 );
    R.drawLine( 220, 480, 260, 480 );
    R.drawLine( 260, 480, 260, 520 );
    R.drawLine( 260, 520, 220, 560 );  // 135 degree slope
    R.drawLine( 220, 560,  80, 560 );
    R.drawLine(  80, 560,  40, 520 );  // 225 degree slope
    R.drawLine(  40, 520,  40, 380 );  // Vertical top to bottom

    // ######## The letter 'O' in red ########

    R.C.setColor( 1.0, 0.0, 0.0 );

    R.drawLine( 450, 320, 520, 340 );  // 16.6 degree slope
    R.drawLine( 520, 340, 540, 360 );  // 45 degree slope
    R.drawLine( 540, 360, 560, 430 );  // 77.47 degree slope
    R.drawLine( 560, 430, 540, 540 );  // 102.83 degree slope
    R.drawLine( 540, 540, 520, 560 );  // 135 degree slope
    R.drawLine( 520, 560, 450, 580 );  // 163.3 degree slope
    R.drawLine( 450, 580, 380, 560 );  // 196.71 degree slope
    R.drawLine( 380, 560, 360, 540 );  // 225 degree slope
    R.drawLine( 360, 540, 340, 450 );  
    R.drawLine( 340, 450, 360, 360 );
    R.drawLine( 360, 360, 380, 340 );
    R.drawLine( 380, 340, 450, 320 );
    R.drawLine( 420, 380, 480, 380 );
    R.drawLine( 480, 380, 520, 420 );
    R.drawLine( 520, 420, 520, 480 );
    R.drawLine( 520, 480, 480, 520 );
    R.drawLine( 480, 520, 420, 520 );
    R.drawLine( 420, 520, 380, 480 );
    R.drawLine( 380, 480, 380, 420 );
    R.drawLine( 380, 420, 420, 380 );

    // now, draw the student's initials

    R.myInitials();

}

//
// create the shapes and fill all the buffers
//
void createImage( void )
{
    // draw all our lines
    makeLines( *rasterizer );

    shapes.createBuffers( rasterizer->C );
}


// OpenGL initialization
void init( void )
{
    // Create our Canvas and Rasterizer "objects"
    Canvas *C = new Canvas( w_width, w_height );
    rasterizer = new Rasterizer( w_height, *C );

    // Load shaders and use the resulting shader program
    ShaderError error;
    if( useAltShaders ) {
        cerr << "Falling back to GLSL 1.20 shaders" << endl;
        program = shaderSetup( "alt.vert", "alt.frag", &error );
    } else {
        program = shaderSetup( "shader.vert", "shader.frag", &error );
    }
    if (!program) {
        cerr << "Error setting up shaders - "
            << errorString(error) << endl;
	glfwTerminate();
        exit(1);
    }

    // OpenGL state initialization
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

    // create the geometry for our shapes.
    createImage();
}


//
// selectBuffers() - bind the correct vertex and element buffers
//
// @param program - GLSL program object
// @param B       - the BufferSet to update
//
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

    // bind our buffers
    selectBuffers( program, shapes );

    // set up our scale factors for normalization
    GLuint sf = glGetUniformLocation( program, "sf" );
    glUniform2f( sf, 2.0f / (w_width - 1.0f), 2.0f / (w_height - 1.0f) );

    // draw our shape
    glDrawArrays( GL_POINTS, 0, shapes.numElements );
}


void keyboard( GLFWwindow *window, int key, int scan, int action, int mods )
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


int main( int argc, char **argv )
{
    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 1 - Line Drawing", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: "
             << glewGetErrorString(err) << endl;
        glfwTerminate();
        exit( 1 );
    }
    if( ! GLEW_VERSION_3_2 ) {
        cerr << "GLEW: OpenGL 3.2 not available" << endl;
	if( !GLEW_VERSION_2_1 ) {
            cerr << "OpenGL 2.1 not available, either!" << endl;
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
