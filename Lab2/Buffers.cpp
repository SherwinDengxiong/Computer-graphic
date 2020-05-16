//
//  Buffers.cpp
//
//  Vertex and element buffer implementations.
//
//  Author:  Warren R. Carithers
//  Date:    2017/02/11 22:34:54
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

//
// GLEW and GLFW header files also pull in the OpenGL definitions
//

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Buffers.h"
#include "Canvas.h"

///
// Constructor
///
BufferSet::BufferSet( void ) {
    // do this the easy way
    initBuffer();
}

///
// initBuffer() - reset the supplied BufferSet to its "empty" state
///
void BufferSet::initBuffer( void ) {
    vbuffer = ebuffer = 0;
    numElements = 0;
    vSize = eSize = tSize = cSize = 0;
    bufferInit = false;
}

///
// makeBuffer() - make a vertex or element array buffer
//
// @param target - which type of buffer to create
// @param data   - source of data for buffer (or NULL)
// @param size   - desired length of buffer
//
// @return the ID of the new buffer
//
GLuint BufferSet::makeBuffer( GLenum target, const void *data, GLsizei size ) {
    GLuint buffer;

    glGenBuffers( 1, &buffer );
    glBindBuffer( target, buffer );
    glBufferData( target, size, data, GL_STATIC_DRAW );

    return( buffer );
}

///
// createBuffers(buf,canvas) create a set of buffers for the object
//     currently held in 'canvas'.
//
// @param C   - the Canvas we'll use for drawing
///
void BufferSet::createBuffers( Canvas &C ) {

    // get the vertices
    numElements = C.numVertices();
    float *points = C.getVertices();
    // #bytes = number of elements * 4 floats/element * bytes/float
    vSize = numElements * 4 * sizeof(float);
    int vbufSize = vSize;

    // get the color data
    float *colors = C.getColors();
    cSize = numElements * 4 * sizeof(float);
    vbufSize += cSize;

    // get the element data
    GLuint *elements = C.getElements();
    // #bytes = number of elements * bytes/element
    eSize = numElements * sizeof(GLuint);

    // set up the vertex buffer
    if( bufferInit ) {
        // must delete the existing buffer IDs first
        glDeleteBuffers( 1, &(vbuffer) );
        glDeleteBuffers( 1, &(ebuffer) );
        initBuffer();
    }

    // first, create the connectivity data
    ebuffer = makeBuffer( GL_ELEMENT_ARRAY_BUFFER, elements, eSize );

    // next, the vertex buffer, containing vertices and "extra" data
    vbuffer = makeBuffer( GL_ARRAY_BUFFER, NULL, vbufSize );
    glBufferSubData( GL_ARRAY_BUFFER, 0, vSize, points );
    glBufferSubData( GL_ARRAY_BUFFER, vSize, cSize, colors );

    // NOTE:  'points', 'colors', and 'elements' are dynamically allocated,
    // but we don't free them here because they will be freed at the next
    // call to clear() or the get*() functions

    // finally, mark it as set up
    bufferInit = true;
}
