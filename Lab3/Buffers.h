//
//  Buffers.h
//
//  Vertex and element buffer management
//
//  Author:  Warren R. Carithers
//  Date:    2017/02/11 22:34:54
//

#ifndef _BUFFERS_H_
#define _BUFFERS_H_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

using namespace std;

#include "Canvas.h"

///
// All the relevant information needed to keep
// track of vertex and element buffers
///

class BufferSet {

public:
    // buffer handles
    GLuint vbuffer, ebuffer;

    // total number of vertices
    int numElements;

    // component sizes (bytes)
    long vSize, eSize, tSize, cSize;

    // have these already been set up?
    bool bufferInit;

public:

    ///
    // Constructor
    ///
    BufferSet( void );

    ///
    // initBuffer(buf) - reset the supplied buffer to its "empty" state
    //
    // @param buf - which buffer to reset
    ///
    void initBuffer( void );

    ///
    // makeBuffer(target,data,size) - make a vertex or element array buffer
    //
    // @param target - which type of buffer to create
    // @param data   - source of data for buffer (or NULL)
    // @param size   - desired length of buffer
    //
    // @return the ID of the new buffer
    ///
    GLuint makeBuffer( GLenum target, const void *data, GLsizei size );

    ///
    // createBuffers(buf,canvas) - create a set of buffers for the object
    //     currently held in 'canvas'.
    //
    // @param C   - the Canvas we'll use for drawing
    ///
    void createBuffers( Canvas &C );

};

#endif
