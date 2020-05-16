//
//  viewParams
//
//  Created by Joe Geigel on 1/23/13.
//
//  This code can be compiled as either C or C++.
//

#include "viewParams.h"

// current values for transformations
GLfloat rotateDefault[3]    = { 0.0f, 50.0f, 90.0f };
GLfloat translateDefault[3] = { 1.0f, 0.0f, -1.0f };
GLfloat scaleDefault[3]     = { 1.0f, 4.0f, 1.0f };

// current view values
GLfloat eyeDefault[3]  = { 0.0f, 3.0f, 3.0f };
GLfloat lookDefault[3] = { 1.0f, 0.0f, 0.0f };
GLfloat upDefault[3]   = { 0.0f, 1.0f, 0.0f };

// clipping window boundaries
GLfloat left   = -1.0f;
GLfloat right  = 1.0f;
GLfloat top    = 1.0f;
GLfloat bottom = -1.0f;
GLfloat near_  = 3.0f; // near is defined in minwindef.h -> replaced by near_
GLfloat far_   = 100.5f; // far is defined in minwindef.h -> replaced by far_


/**
 * This function sets up the view and projection parameter for a frustum
 * projection of the scene. See the assignment description for the values
 * for the projection parameters.
 *
 * You will need to write this function, and maintain all of the values
 * needed to be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 *
 */
void setUpFrustum( GLuint program )
{
    GLuint leftLoc = glGetUniformLocation( program, "left" );
    GLuint rightLoc = glGetUniformLocation( program, "right" );
    GLuint topLoc = glGetUniformLocation( program, "top" );
    GLuint bottomLoc = glGetUniformLocation( program, "bottom" );
    GLuint nearLoc = glGetUniformLocation( program, "near" );
    GLuint farLoc = glGetUniformLocation( program, "far" );

    glUniform1f( leftLoc, left );
    glUniform1f( rightLoc, right );
    glUniform1f( topLoc, top );
    glUniform1f( bottomLoc, bottom );
    glUniform1f( nearLoc, near_ );
    glUniform1f( farLoc, far_ );
}


/**
 * This function clears any transformations, setting the values to the
 * defaults: scale by 4 in Y, rotate by 50 in Y and 90 in Z, and
 * translate by 1 in X and -1 in Z.
 *
 * You will need to write this function, and maintain all of the values
 * which must be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 *
 */
void clearTransforms( GLuint program )
{
    // reset the shader using global data
    GLuint thetaLoc = glGetUniformLocation( program, "theta" );
    GLuint transLoc = glGetUniformLocation( program, "trans" );
    GLuint scaleLoc = glGetUniformLocation( program, "scale" );

    glUniform3fv( thetaLoc, 1, rotateDefault );
    glUniform3fv( transLoc, 1, translateDefault );
    glUniform3fv( scaleLoc, 1, scaleDefault );

}


/**
 * This function sets up the transformation parameters for the vertices
 * of the teapot.  The order of application is specified in the driver
 * program.
 *
 * You will need to write this function, and maintain all of the values
 * which must be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 * @param scaleX - amount of scaling along the x-axis
 * @param scaleY - amount of scaling along the y-axis
 * @param scaleZ - amount of scaling along the z-axis
 * @param rotateX - angle of rotation around the x-axis, in degrees
 * @param rotateY - angle of rotation around the y-axis, in degrees
 * @param rotateZ - angle of rotation around the z-axis, in degrees
 * @param translateX - amount of translation along the x axis
 * @param translateY - amount of translation along the y axis
 * @param translateZ - amount of translation along the z axis
 */
void setUpTransforms( GLuint program,
    GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
    GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ,
    GLfloat translateX, GLfloat translateY, GLfloat translateZ )
{
    GLfloat scaleVec[]     = { scaleX, scaleY, scaleZ };
    GLfloat rotateVec[]    = { rotateX, rotateY, rotateZ };
    GLfloat translateVec[] = { translateX, translateY, translateZ };

    GLuint thetaLoc = glGetUniformLocation( program, "theta" );
    GLuint transLoc = glGetUniformLocation( program, "trans" );
    GLuint scaleLoc = glGetUniformLocation( program, "scale" );

    // send down to the shader
    glUniform3fv( thetaLoc, 1, rotateVec );
    glUniform3fv( transLoc, 1, translateVec );
    glUniform3fv( scaleLoc, 1, scaleVec );
}


/**
 * This function clears any changes made to camera parameters, setting the
 * values to the defaults: eyepoint (0.0,3.0,3.0), lookat (1,0,0.0,0.0),
 * and up vector (0.0,1.0,0.0).
 *
 * You will need to write this function, and maintain all of the values
 * which must be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 */
void clearCamera( GLuint program )
{
    GLuint posLoc = glGetUniformLocation( program, "cPosition" );
    GLuint lookLoc = glGetUniformLocation( program, "cLookAt" );
    GLuint upVecLoc = glGetUniformLocation( program, "cUp" );

    glUniform3fv( posLoc, 1, eyeDefault );
    glUniform3fv( lookLoc, 1, lookDefault );
    glUniform3fv( upVecLoc, 1, upDefault );

}

/**
 * This function sets up the camera parameters controlling the viewing
 * transformation.
 *
 * You will need to write this function, and maintain all of the values
 * which must be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 * @param eyepointX - x coordinate of the camera location
 * @param eyepointY - y coordinate of the camera location
 * @param eyepointZ - z coordinate of the camera location
 * @param lookatX - x coordinate of the lookat point
 * @param lookatY - y coordinate of the lookat point
 * @param lookatZ - z coordinate of the lookat point
 * @param upX - x coordinate of the up vector
 * @param upY - y coordinate of the up vector
 * @param upZ - z coordinate of the up vector
 */
void setUpCamera( GLuint program,
    GLfloat eyepointX, GLfloat eyepointY, GLfloat eyepointZ,
    GLfloat lookatX, GLfloat lookatY, GLfloat lookatZ,
    GLfloat upX, GLfloat upY, GLfloat upZ )
{
    GLfloat eyeVec[]    = { eyepointX, eyepointY, eyepointZ };
    GLfloat lookatVec[] = { lookatX, lookatY, lookatZ };
    GLfloat upVec[]     = { upX, upY, upZ };

    GLuint posLoc = glGetUniformLocation( program, "cPosition" );
    GLuint lookLoc = glGetUniformLocation( program, "cLookAt" );
    GLuint upVecLoc = glGetUniformLocation( program, "cUp" );

    // send down to the shader
    glUniform3fv( posLoc, 1, eyeVec );
    glUniform3fv( lookLoc, 1, lookatVec );
    glUniform3fv( upVecLoc, 1, upVec );
}
