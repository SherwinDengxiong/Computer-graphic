//
//  Viewing
//
//  Created by Warren R. Carithers 2016/11/11.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Simple class for setting up the viewing and projection transforms
//  for the Transformation Assignment.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  YOUR_NAME_HERE
//

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Viewing.h"

///
// This function sets up the view and projection parameter for a frustum
// projection of the scene. See the assignment description for the values
// for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpFrustum( GLuint program )
{
    // Add your code here.
    glUniform1f(glGetUniformLocation(program, "Projectiontype"), 1.0);
}


///
// This function sets up the view and projection parameter for an
// orthographic projection of the scene. See the assignment description
// for the values for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpOrtho( GLuint program )
{
    // Add your code here.
    glUniform1f(glGetUniformLocation(program, "Projectiontype"), 2.0);
}


///
// This function clears any model transformations, setting the values
// to the defaults: no scaling (scale factor of 1), no rotation (degree
// of rotation = 0), and no translation (0 translation in each direction).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearTransforms( GLuint program )
{
    // Add your code here.
    GLfloat ro[] = { 0.0, 0.0, 0.0 };
    GLfloat scal[] = { 1.0, 1.0, 1.0 };
    GLfloat trans[] = { 0.0, 0.0, 0.0 };

    glUniform3fv(glGetUniformLocation(program, "rota"), 1, ro);
    glUniform3fv(glGetUniformLocation(program, "scal"), 1, scal);
    glUniform3fv(glGetUniformLocation(program, "transform"), 1, trans);
}


///
// This function sets up the transformation parameters for the vertices
// of the teapot.  The order of application is specified in the driver
// program.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param scaleX - amount of scaling along the x-axis
// @param scaleY - amount of scaling along the y-axis
// @param scaleZ - amount of scaling along the z-axis
// @param rotateX - angle of rotation around the x-axis, in degrees
// @param rotateY - angle of rotation around the y-axis, in degrees
// @param rotateZ - angle of rotation around the z-axis, in degrees
// @param translateX - amount of translation along the x axis
// @param translateY - amount of translation along the y axis
// @param translateZ - amount of translation along the z axis
///
void setUpTransforms( GLuint program,
    GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
    GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ,
    GLfloat translateX, GLfloat translateY, GLfloat translateZ )
{
    // Add your code here.
    GLfloat scal[] = { scaleX, scaleY, scaleZ };
    GLfloat ro[] = { rotateX, rotateY, rotateZ };
    GLfloat trans[] = { translateX, translateY, translateZ };

    glUniform3fv(glGetUniformLocation(program, "rota"), 1, ro);
    glUniform3fv(glGetUniformLocation(program, "scal"), 1, scal);
    glUniform3fv(glGetUniformLocation(program, "transform"), 1, trans);
}


///
// This function clears any changes made to camera parameters, setting the
// values to the defaults: eye (0.0,0.0,0.0), lookat (0,0,0.0,-1.0),
// and up vector (0.0,1.0,0.0).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearCamera( GLuint program )
{
    // Add your code here.
    GLfloat camera[] = { 0.0, 0.0, 0.0 };
    GLfloat look[] = { 0.0, 0.0, -1.0 };
    GLfloat up[] = { 0.0, 1.0, 0.0 };

    glUniform3fv(glGetUniformLocation(program, "lookat"), 1, look);
    glUniform3fv(glGetUniformLocation(program, "eye"), 1, camera);
    glUniform3fv(glGetUniformLocation(program, "up"), 1, up);
}

///
// This function sets up the camera parameters controlling the viewing
// transformation.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param eyeX - x coordinate of the camera location
// @param eyeY - y coordinate of the camera location
// @param eyeZ - z coordinate of the camera location
// @param lookatX - x coordinate of the lookat point
// @param lookatY - y coordinate of the lookat point
// @param lookatZ - z coordinate of the lookat point
// @param upX - x coordinate of the up vector
// @param upY - y coordinate of the up vector
// @param upZ - z coordinate of the up vector
///
void setUpCamera( GLuint program,
    GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
    GLfloat lookatX, GLfloat lookatY, GLfloat lookatZ,
    GLfloat upX, GLfloat upY, GLfloat upZ )
{
    // Add your code here.
    GLfloat camera[] = { eyeX, eyeY, eyeZ };
    GLfloat look[] = { lookatX, lookatY, lookatZ };
    GLfloat up[] = { upX, upY, upZ };

    
    glUniform3fv(glGetUniformLocation(program, "lookat"), 1, look);
    glUniform3fv(glGetUniformLocation(program, "up"), 1, up);
    glUniform3fv(glGetUniformLocation(program, "eye"), 1, camera);
}
