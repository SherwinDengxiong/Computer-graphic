//
// simpleShape.cpp
//
// routines for adding triangles to create a new mesh
//
// Students are not to modify this file.
//

#include <vector>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include "simpleShape.h"

using namespace std;

/**
 * common variables...should probably make this a class and make these
 * data members
 */
vector<float> points;
vector<float> normals;
float *pointArray = 0;
float *normalArray = 0;
GLushort *elemArray = 0;


/**
 * clear the current shape
 */
void clearShape( void )
{
    if (pointArray) {
        delete pointArray;
        delete elemArray;
        delete normalArray;
        pointArray = 0;
        elemArray = 0;
        normalArray = 0;
    }
    points.clear();
    normals.clear();
}


/**
 * adds a triangle to the current shape using calculated normals
 */
void addTriangle(
    float x0, float y0, float z0,
    float x1, float y1, float z1,
    float x2, float y2, float z2 )
{
    // calculate the normal
    float ux = x1 - x0;
    float uy = y1 - y0;
    float uz = z1 - z0;

    float vx = x2 - x0;
    float vy = y2 - y0;
    float vz = z2 - z0;

    float nx = (uy * vz) - (uz * vy);
    float ny = (uz * vx) - (ux * vz);
    float nz = (ux * vy) - (uy * vx);

    // Attach the normal to all 3 vertices
    addTriangleWithNorms(
        x0, y0, z0, x1, y1, z1, x2, y2, z2,
        nx, ny, nz, nx, ny, nz, nx, ny, nz
    );
}


/**
 * adds a triangle to the current shape using supplied normals
 */
void addTriangleWithNorms(
    float x0, float y0, float z0,
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float nx0, float ny0, float nz0,
    float nx1, float ny1, float nz1,
    float nx2, float ny2, float nz2 )
{
    points.push_back( x0 );
    points.push_back( y0 );
    points.push_back( z0 );
    points.push_back( 1.0f );

    normals.push_back( nx0 );
    normals.push_back( ny0 );
    normals.push_back( nz0 );

    points.push_back( x1 );
    points.push_back( y1 );
    points.push_back( z1 );
    points.push_back( 1.0f );

    normals.push_back( nx1 );
    normals.push_back( ny1 );
    normals.push_back( nz1 );

    points.push_back( x2 );
    points.push_back( y2 );
    points.push_back( z2 );
    points.push_back( 1.0f );

    normals.push_back( nx2 );
    normals.push_back( ny2 );
    normals.push_back( nz2 );

}


/**
 * gets the vertex points for the current shape
 */
float *getVertices( void )
{
    // delete the old point array of we have one
    if( pointArray ) {
        delete [] pointArray;
    }

    // create and fill a new point array
    pointArray = new float[points.size()];
    for( unsigned int i=0; i < points.size(); i++ ) {
        pointArray[i] = points[i];
    }

    return pointArray;
}


/**
 * gets the normals for the current shape
 */
float *getNormals( void )
{
    // delete the old point array of we have one
    if( normalArray ) {
        delete [] normalArray;
    }

    // create and fill a new point array
    normalArray = new float[normals.size()];
	for ( unsigned int i = 0; i < normals.size(); i++) {
        normalArray[i] = normals[i];
    }

    return normalArray;
}


/**
 * gets the  array of elements for the  current shape
 */
GLushort *getElements( void )
{
    // delete the old point array of we have one
    if( elemArray ) {
        delete [] elemArray;
    }

    // create and fill a new point array
    elemArray = new GLushort[points.size()];
	for ( unsigned int i = 0; i < points.size(); i++) {
        elemArray[i] = i;
    }

    return elemArray;
}


/**
 * returns number of vertices in current shape
 */
int nVertices( void )
{
    return points.size() / 4;
}
