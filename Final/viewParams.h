//
//  viewParams.h
//
//  Created by Joe Geigel on 1/23/13.
//

#ifndef _VIEWPARAMS_H_
#define _VIEWPARAMS_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#endif

void setUpFrustum( GLuint program );
void setUpOrtho( GLuint program );

void clearTransforms( GLuint program );
void setUpTransforms( GLuint program,
    GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
    GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ,
    GLfloat translateX, GLfloat translateY, GLfloat translateZ );

void clearCamera( GLuint program );
void setUpCamera( GLuint program,
    GLfloat eyepointX, GLfloat eyepointY, GLfloat eyepointZ,
    GLfloat lookatX, GLfloat lookatY, GLfloat lookatZ,
    GLfloat upX, GLfloat upY, GLfloat upZ );

#endif
