//
//  Shapes.h
//
//  Prototypes for tessellation routines to be supplied by students.
//
//  Students should not modify this file.
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Canvas.h"

///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivisions - number of equal subdivisons to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions );

///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions );

///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions );

///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slides - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks );

#endif
