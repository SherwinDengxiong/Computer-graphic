//
//  fillMain
//
//  Main program for polygon fill assignment
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
#include "Buffers.h"
#include "Canvas.h"
#include "Rasterizer.h"

using namespace std;

// dimensions of drawing window
int w_width  = 900;
int w_height = 600;

// how to calculate an offset into the vertex buffer
#define	BUFFER_OFFSET(i)	((char *)NULL + (i))

// our Rasterizer
Rasterizer *rasterizer;

// buffer information
BufferSet shapes;

// shader program ID
GLuint program;

// "fall back" to GLSL 1.20 shaders?
bool useAltShaders = false;

///
// Create all the polygons and draw them using the Rasterizer
///
void makePolygons( Rasterizer &R )
{
    // start with a clean canvas
    R.C.clear();

    // make these large enough for any of our polygons
    int x[10];
    int y[10];

    // ########### TEAPOT START ###########
    // BASE
    x[0] = 760;  y[0] =  40;
    x[1] = 600;  y[1] =  40;
    x[2] = 620;  y[2] =  60;
    x[3] = 740;  y[3] =  60;
    R.C.setColor( 1.0f, 0.0f, 0.0f );
    R.drawPolygon( 4, x, y );

    // RIGHT BOTTOM TRIANGLE
    x[0] = 800;  y[0] = 120;
    x[1] = 740;  y[1] =  60;
    x[2] = 620;  y[2] =  60;
    R.C.setColor( 0.9f, 0.0f, 0.0f );
    R.drawPolygon( 3, x, y );

    // SPOUT
    x[0] = 620;  y[0] =  60;
    x[1] = 560;  y[1] = 100;
    x[2] = 500;  y[2] = 180;
    R.C.setColor( 0.8f, 0.0f, 0.0f );
    R.drawPolygon( 3, x, y );

    x[0] = 620;  y[0] =  60;
    x[1] = 500;  y[1] = 180;
    x[2] = 460;  y[2] = 200;
    x[3] = 520;  y[3] = 200;
    x[4] = 580;  y[4] = 160;
    R.C.setColor( 0.7f, 0.0f, 0.0f );
    R.drawPolygon( 5, x, y );

    x[0] = 620;  y[0] =  60;
    x[1] = 580;  y[1] = 160;
    x[2] = 620;  y[2] = 240;
    x[3] = 740;  y[3] = 240;
    x[4] = 800;  y[4] = 120;
    R.C.setColor( 0.6f, 0.0f, 0.0f );
    R.drawPolygon( 5, x, y );

    x[0] = 800;  y[0] = 120;
    x[1] = 840;  y[1] = 160;
    x[2] = 855;  y[2] = 200;
    x[3] = 720;  y[3] = 220;
    x[4] = 720;  y[4] = 200;
    x[5] = 830;  y[5] = 190;
    x[6] = 825;  y[6] = 165;
    x[7] = 780;  y[7] = 120;
    R.C.setColor( 0.5f, 0.0f, 0.0f );
    R.drawPolygon( 8, x, y );

    x[0] = 690;  y[0] = 240;
    x[1] = 710;  y[1] = 260;
    x[2] = 650;  y[2] = 260;
    x[3] = 670;  y[3] = 240;
    R.C.setColor( 0.4f, 0.0f, 0.0f );
    R.drawPolygon( 4, x, y );

    // ######## TRIANGLE #######
    x[0] = 460;  y[0] = 220;
    x[1] = 490;  y[1] = 280;
    x[2] = 420;  y[2] = 280;
    R.C.setColor( 0.0f, 1.0f, 0.0f );
    R.drawPolygon( 3, x, y );

    // ########## QUAD ##########
    x[0] = 380;  y[0] = 280;
    x[1] = 320;  y[1] = 320;
    x[2] = 360;  y[2] = 380;
    x[3] = 420;  y[3] = 340;
    R.C.setColor( 0.0f, 0.8f, 0.8f );
    R.drawPolygon( 4, x, y );

    // ############ STAR #############
    // RIGHT SIDE
    x[0] = 230;  y[0] = 389;
    x[1] = 260;  y[1] = 369;
    x[2] = 254;  y[2] = 402;
    x[3] = 278;  y[3] = 425;
    x[4] = 245;  y[4] = 430;
    x[5] = 230;  y[5] = 460;
    x[6] = 230;  y[6] = 410;
    R.C.setColor( 0.8f, 0.8f, 0.0f );
    R.drawPolygon( 7, x, y );

    // LEFT SIDE
    x[0] = 230;  y[0] = 460;
    x[1] = 216;  y[1] = 430;
    x[2] = 183;  y[2] = 425;
    x[3] = 207;  y[3] = 402;
    x[4] = 201;  y[4] = 369;
    x[5] = 230;  y[5] = 389;
    x[6] = 230;  y[6] = 410;
    R.C.setColor( 0.7f, 0.7f, 0.0f );
    R.drawPolygon( 7, x, y );

    // ########## BORDERS ###############
    // SQUARE BOTTOM LEFT
    x[0] =   0;  y[0] =   0;
    x[1] =   0;  y[1] =  20;
    x[2] =  20;  y[2] =  20;
    x[3] =  20;  y[3] =   0;
    R.C.setColor( 0.0f, 0.0f, 1.0f );
    R.drawPolygon( 4, x, y );

    x[0] =   0;  y[0] =  10;
    x[1] =  10;  y[1] =  10;
    x[2] =  10;  y[2] = 580;
    x[3] =   0;  y[3] = 580;
    R.C.setColor( 0.0f, 0.1f, 0.9f );
    R.drawPolygon( 4, x, y );

    x[0] =   0;   y[0] = 580;
    x[1] =   0;  y[1] = 599;
    x[2] =  20;  y[2] = 599;
    x[3] =  20;  y[3] = 580;
    R.C.setColor( 0.0f, 0.2f, 0.8f );
    R.drawPolygon( 4, x, y );

    //  TRIANGLE TOP:TOP
    x[0] =  10;  y[0] = 590;
    x[1] =  10;  y[1] = 599;
    x[2] = 880;  y[2] = 599;
    R.C.setColor( 0.0f, 0.3f, 0.7f );
    R.drawPolygon( 3, x, y );

    //  TRIANGLE TOP:BOTTOM
    x[0] =  10;  y[0] = 590;
    x[1] = 880;  y[1] = 590;
    x[2] = 880;  y[2] = 599;
    R.C.setColor( 0.0f, 0.4f, 0.6f );
    R.drawPolygon( 3, x, y );

    // SQUARE TOP RIGHT
    x[0] = 899;  y[0] = 599;
    x[1] = 899;  y[1] = 580;
    x[2] = 880;  y[2] = 580;
    x[3] = 880;  y[3] = 599;
    R.C.setColor( 0.1f, 0.4f, 0.5f );
    R.drawPolygon( 4, x, y );

    //  TRIANGLE RIGHT:RIGHT
    x[0] = 890;  y[0] = 580;
    x[1] = 899;  y[1] = 580;
    x[2] = 890;  y[2] =  20;
    R.C.setColor( 0.2f, 0.4f, 0.4f );
    R.drawPolygon( 3, x, y );

    //  TRIANGLE RIGHT:LEFT
    x[0] = 899;  y[0] = 580;
    x[1] = 899;  y[1] =  20;
    x[2] = 890;  y[2] =  20;
    R.C.setColor( 0.3f, 0.4f, 0.3f );
    R.drawPolygon( 3, x, y );

    // SQUARE BOTTOM RIGHT
    x[0] = 899;  y[0] =   0;
    x[1] = 899;  y[1] =  20;
    x[2] = 880;  y[2] =  20;
    x[3] = 880;  y[3] =   0;
    R.C.setColor( 0.4f, 0.4f, 0.2f );
    R.drawPolygon( 4, x, y );

    // QUAD BOTTOM
    x[0] =  20;  y[0] =   0;
    x[1] =  20;  y[1] =  10;
    x[2] = 880;  y[2] =  10;
    x[3] = 880;  y[3] =   0;
    R.C.setColor( 0.4f, 0.5f, 0.1f );
    R.drawPolygon( 4, x, y );
}

//
// create the shapes and fill all the buffers
//
void createImage( void )
{
    // draw all our polygons
    makePolygons( *rasterizer );

    shapes.createBuffers( rasterizer->C );
}

///
// OpenGL initialization
///
void init( void )
{
    // Create our Canvas and Rasterizer "objects"
    Canvas *C = new Canvas( w_width, w_height );
    rasterizer = new Rasterizer( w_height, *C );

    if( C == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
	glfwTerminate();
        exit( 1 );
    }

    if( rasterizer == NULL ) {
        cerr << "error - cannot create Rasterizer" << endl;
	glfwTerminate();
        exit( 1 );
    }

    // Load shaders and use the resulting shader program
    ShaderError error;
    if( useAltShaders ) {
	cerr << "Falling back to GLSL 1.20 shaders" << endl;
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
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
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

    // bind our buffers
    selectBuffers( program, shapes );

    // set up our scale factors for normalization
    GLuint sf = glGetUniformLocation( program, "sf" );
    glUniform2f( sf, 2.0f / (w_width - 1.0f), 2.0f / (w_height - 1.0f) );

    // draw our shape
    glDrawElements( GL_POINTS, shapes.numElements, GL_UNSIGNED_INT, (void *)0 );
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
// main program for polygon fill assignment
///
int main( int argc, char *argv[] )
{
    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 2 - Polygon Fill", NULL, NULL );

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
