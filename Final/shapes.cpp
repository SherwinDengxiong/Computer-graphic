//
// shapes
//
// Routines for shape-drawing functions.
//
// This code can be compiled as either C or C++.
//

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include <Windows.h>
#endif

#include "simpleShape.h"
#include "shapes.h"

#ifdef __cplusplus
#include <cmath>
using namespace std;
#else
#include <math.h>
#endif

///
// makeRectangle - Create polygons for a rectangle
//
// Can only use calls to addTriangle()
///
void makeRectangle(float dx, float dy, float dz, float _x, float _y, float _z) {
	// some aliases p: plus, m: minus
	float px = dx / 2.0f + _x, mx = -dx / 2.0f + _x;
	float py = dy / 2.0f + _y, my = -dy / 2.0f + _y;
	float pz = dz / 2.0f + _z, mz = -dz / 2.0f + _z;

	// face (x,y,-1) drawn clockwise
	addTriangle(px, my, mz, mx, py, mz, px, py, mz);
	addTriangle(px, my, mz, mx, my, mz, mx, py, mz);
	// face (x,y,1) drawn counterclockwise
	addTriangle(px, my, pz, px, py, pz, mx, py, pz);
	addTriangle(px, my, pz, mx, py, pz, mx, my, pz);
	// face (-.5,y,z) drawn counterclockwise
	addTriangle(mx, my, mz, mx, py, pz, mx, py, mz);
	addTriangle(mx, my, mz, mx, my, pz, mx, py, pz);
	// face (.5,y,z) drawn clockwise
	addTriangle(px, my, mz, px, py, mz, px, py, pz);
	addTriangle(px, my, mz, px, py, pz, px, my, pz);
	// face (x,-.5,z) drawn clockwise
	addTriangle(mx, my, mz, px, my, pz, mx, my, pz);
	addTriangle(mx, my, mz, px, my, mz, px, my, pz);
	// face (x,.5,z) drawn counterclockwise
	addTriangle(mx, py, mz, mx, py, pz, px, py, pz);
	addTriangle(mx, py, mz, px, py, pz, px, py, mz);
}

///
// makeCylinder - Create polygons for a cylinder
//
// Can only use calls to addTriangle()
///
void makeCylinder(float radius, float len, float _x, float _y, float _z)
{
	int	radialDivisions = 10;

	const float PI = 3.14159265358979f;
	float alpha = 0,
		z0 = -.5, z1,
		x0, y0, x1, y1;
	for (int i = 0; i < radialDivisions; i++) {
		// we compute the coordinates of the triangle MON, 
		// where M(x0,+/-.5,z0), O(0,+/-.5,0) and N(x1,+/-.5,z1)
		x0 = radius * cosf((float)i * 2 * PI / (float)radialDivisions);
		y0 = radius * sinf((float)i * 2 * PI / (float)radialDivisions);
		x1 = radius * cosf((float)(i + 1) * 2 * PI / (float)radialDivisions);
		y1 = radius * sinf((float)(i + 1) * 2 * PI / (float)radialDivisions);

		// face (x,-.5,z) drawn clockwise
		//addTriangle(_x, _z, -len / 2 + _y, x1 + _x, y1 + _z, -len / 2 + _y, x0 + _x, y0 + _z, -len / 2 + _y);
		// face (x,5,z) drawn counterclockwise
		addTriangle(x1+_x, y1+_y, len / 2 +_z, _x, _y, len / 2 + _z, x0 + _x, y0 + _y, len / 2 + _z);

		
		z0 = _z - len / 2;
		z1 = _z + len / 2;
		//addTriangle(x0, y1, z0, x1, y1, z1, x0, y0, z0);
		//addTriangle(x1, y1, z1, x1, y0, z1, x0, y0, z0);
		addTriangle(x0 + _x, y0 + _y, z1, x0 + _x, y0 + _y, z0, x1 + _x, y1 + _y, z1);
		addTriangle(x1 + _x, y1 + _y, z1, x0 + _x, y0 + _y, z0, x1 + _x, y1 + _y, z0);
	}
}

///
// makeCone - Create polygons for a cone
//
// Can only use calls to addTriangle()
///
void makeCone(float radius, float len, float _x, float _y, float _z)
{
	int radialDivisions = 10;
	int	heightDivisions = 1;

	const float PI = 3.14159265358979f;

	for (int i = 0; i < radialDivisions; i++) {
		// we compute the coordinates of the triangle MON, 
		// where M(x0,+/-.5,z0), O(0,+/-.5,0) and N(x1,+/-.5,z1)
		float x0 = radius * cosf(i * 2 * PI / radialDivisions);
		float y0 = radius * sinf(i * 2 * PI / radialDivisions);
		float x1 = radius * cosf((i + 1) * 2 * PI / radialDivisions);
		float y1 = radius * sinf((i + 1) * 2 * PI / radialDivisions);

		// face (x,5,z) drawn counterclockwise
		addTriangle(x1 + _x, y1 + _y, -len / 2 + _z, x0 + _x, y0 + _y, -len / 2 + _z, _x, _y, -len / 2 + _z);

		float z0 = _z - len / 2;
		float z1 = _z + len / 2;

		// when we are at the top of the cone, just draw a triangle
		addTriangle(x0 + _x, y0 + _y, z0, x1 + _x, y1 + _y, z0, _x, _y, z1);
	}
}

//
// makeFence() - create a torus object
// @param shadingType - indicates flat vs. non-flat shading
//
static void makeFence(int shadingType)
{
	makeRectangle(10, 0.04, 0.04, 0, 0, 0.2f);
	makeRectangle(10, 0.04, 0.04, 0, 0, 0);
	makeRectangle(10, 0.04, 0.04, 0, 0, 1.0f);
	for (int i = -11; i < 12; i++) {
		makeRectangle(0.04, 0.04, 1.2f, 0.3 * i, 0.0f, 0.6f);
	}
}

//
// makeGround() - create a teapot object
// @param shadingType - indicates flat vs. non-flat shading
//
static void makeGround(int shadingType) {
	makeRectangle(10, 4.0f, 0.04, 0, -2.0, -0.04f);
}

//
// makeTardis() - create a teapot object
// @param shadingType - indicates flat vs. non-flat shading
//
static void makeTardis( int shadingType )
{
	// body
	makeRectangle(1.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f);

	// edges
	makeRectangle(0.1f, 0.1f, 2.0f, -0.5f, -0.5f, 0.0f);
	makeRectangle(0.1f, 0.1f, 2.0f, -0.5f, 0.5f, 0.0f);
	makeRectangle(0.1f, 0.1f, 2.0f, 0.5f, -0.5f, 0.0f);
	makeRectangle(0.1f, 0.1f, 2.0f, 0.5f, 0.5f, 0.0f);

	// cap
	makeRectangle(1.1f, 1.1f, 0.2f, 0.0f, 0.0f, 1.1f);
	makeRectangle(1.0f, 1.0f, 0.1f, 0.0f, 0.0f, 1.25f);
	makeRectangle(0.9f, 0.9f, 0.15f, 0.0f, 0.0f, 1.375);

	// socle
	makeRectangle(1.2f, 1.2f, 0.05f, 0.0f, 0.0f, -1.025f);

	// policebox sign
	makeRectangle(1.0f, 0.02f, 0.2f, 0.0f, 0.56f, 1.1f);
	makeRectangle(1.0f, 0.02f, 0.2f, 0.0f, -0.56f, 1.1f);
	makeRectangle(0.02f, 1.0f, 0.2f, 0.56f, 0.0f, 1.1f);
	makeRectangle(0.02f, 1.0f, 0.2f, -0.56f, 0.0f, 1.1f);

	// bulb
	makeRectangle(0.2f, 0.2f, 0.06f, 0.0f, 0.0f, 1.45f);
	makeCylinder(0.06f, 0.16f, 0.0f, 0.0f, 1.56f);
	makeCone(0.08f, 0.04f, 0.0f, 0.0f, 1.67f);
}

/**
* Make either a torus or teapot
* @param choice - 0 for torus. 1 for teapot.
* @param shadingType - 0 for flat, 1 for non-flat
*/
void makeShape( int choice, int shadingType )
{
	if (choice == OBJ_BACKGROUND);
		//makeGround(shadingType);
	else if (choice == OBJ_FENCE) {
		makeFence(shadingType);
	}
	else if (choice == OBJ_GROUND)
		makeGround(shadingType);
	else
		makeTardis(shadingType);
}

