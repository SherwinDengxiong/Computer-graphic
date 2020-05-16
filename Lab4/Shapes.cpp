//
//  Shapes
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  This code can be compiled as either C or C++.
//

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"


///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions )
{
    if( subdivisions < 1 )
        subdivisions = 1;
    //initialize 7corner point
    //subdivisions = 1;
    Vertex corner1 = { -0.5,0.5,0.5 };
    Vertex corner2 = { -0.5,-0.5,0.5 };
    Vertex corner3 = { -0.5,-0.5,-0.5 };
    Vertex corner4 = { 0.5,-0.5,-0.5 };
    Vertex corner5 = { 0.5,0.5,-0.5 };
    Vertex corner6 = { 0.5,-0.5,0.5 };
    Vertex corner7 = { 0.5,0.5,0.5 };
    Vertex corner8 = { -0.5,0.5,-0.5 };
    

    float dx = 0;
    float dy = 0;
    float dz = 0;
    float d = 1 / subdivisions;
    //initialize edges and store division point in the vector
    vector<Vertex> edge12;
    
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner1.x,
                        corner1.y -d*i ,
                        corner1.z  };
        edge12.push_back(temp);
    }
    vector<Vertex> edge26;
    dx = corner2.x - corner6.x;
    dy = corner2.y - corner6.y;
    dz = corner2.z - corner6.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner2.x +d* i,
                        corner2.y  ,
                        corner2.z  };
        edge26.push_back(temp);
    }
    vector<Vertex> edge67;
    dx = corner6.x - corner7.x;
    dy = corner6.y - corner7.y;
    dz = corner6.z - corner7.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner6.x,
                        corner6.y + d * i ,
                        corner6.z };
        edge67.push_back(temp);
    }
    vector<Vertex> edge17;
    dx = corner1.x - corner7.x;
    dy = corner1.y - corner7.y;
    dz = corner1.z - corner7.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner1.x + d * i,
                        corner1.y,
                        corner1.z  };
        edge17.push_back(temp);
    }
    vector<Vertex> edge23;
    dx = corner2.x - corner3.x;
    dy = corner2.y - corner3.y;
    dz = corner2.z - corner3.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner2.x,
                        corner2.y,
                        corner2.z -d * i };
        edge23.push_back(temp);
    }
    vector<Vertex> edge34;
    dx = corner3.x - corner4.x;
    dy = corner3.y - corner4.y;
    dz = corner3.z - corner4.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner3.x +d * i,
                        corner3.y  ,
                        corner3.z };
        edge34.push_back(temp);
    }
    vector<Vertex> edge46;
    dx = corner4.x - corner6.x;
    dy = corner4.y - corner6.y;
    dz = corner4.z - corner6.z;
    for (int i = 0; i <=subdivisions; i++)
    {
        Vertex temp = { corner4.x,
                        corner4.y,
                        corner4.z +d * i };
        edge46.push_back(temp);
    }
    vector<Vertex> edge45;
    dx = corner4.x - corner5.x;
    dy = corner4.y - corner5.y;
    dz = corner4.z - corner5.z;
    for (int i = 0; i <= subdivisions; i++)
    {
        Vertex temp = { corner4.x,
                        corner4.y +d * i ,
                        corner4.z};
        edge45.push_back(temp);
    }
    vector<Vertex> edge57;
    dx = corner5.x - corner7.x;
    dy = corner5.y = corner7.y;
    dz = corner5.z - corner7.z;
    for (int i = 0; i <= subdivisions; i++)
    {
        Vertex temp = { corner5.x,
                        corner5.y ,
                        corner5.z +d * i };
        edge57.push_back(temp);
    }
    vector<Vertex> edge18;
    for (int i = 0; i <= subdivisions; i++)
    {
        Vertex temp = { corner1.x,
                        corner1.y ,
                        corner1.z -d * i };
        edge18.push_back(temp);
    }
    vector<Vertex> edge83;
    for (int i = 0; i <= subdivisions; i++)
    {
        Vertex temp = { corner8.x,
                        corner8.y-d*i ,
                        corner8.z  };
        edge83.push_back(temp);
    }
    vector<Vertex> edge85;
    for (int i = 0; i <= subdivisions; i++)
    {
        Vertex temp = { corner8.x+d*i,
                        corner8.y ,
                        corner8.z };
        edge85.push_back(temp);
    }



    //draw the triangle for each edge
    
    Vertex v1;
    Vertex v2;
    Vertex v3;
    
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge34[t2];
            Vertex temp3 = edge34[t2 + 1];
            v2 = temp2;
                v3 = temp3;
            v1 = { v3.x,v3.y,v3.z+d };
            C.addTriangle(v3, v2, v1);
        }
    }
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge26[t2];
            Vertex temp3 = edge26[t2 + 1];
            v2 = temp2;
            v3 = temp3;
            v1 = { v2.x,v2.y,v2.z - d };
            C.addTriangle(v1, v2, v3);
        }
    }
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge45[t2];
            Vertex temp3 = edge45[t2 + 1];
            v2 = temp2;
            v3 = temp3;
            v1 = { v2.x,v2.y,v2.z + d };
            C.addTriangle(v3, v2, v1);
        }
    }
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge67[t2];
            Vertex temp3 = edge67[t2 + 1];
            v2 = temp2;
            v3 = temp3;
            v1 = { v3.x,v3.y,v3.z -d };
            C.addTriangle(v1, v2, v3);
        }
    }
    
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge34[t2];
            Vertex temp3 = edge34[t2 + 1];
            v2 = temp2;
            v3 = temp3;
            v1 = { v3.x,v3.y+d,v3.z };
            C.addTriangle(v1, v2, v3);
        }
    }
    for (int t1 = 0; t1 < subdivisions; t1++) {
        for (int t2 = 0; t2 < subdivisions; t2++) {

            Vertex temp2 = edge85[t2];
            Vertex temp3 = edge85[t2 + 1];
            v2 = temp2;
            v3 = temp3;
            v1 = { v2.x,v2.y -d,v2.z };
            C.addTriangle(v3, v2, v1);
        }
    }
    
    


    
    
   
   
    
    

    
    



    // YOUR IMPLEMENTATION HERE
}


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
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

    float PI = 3.1415926;
    float d = 1 / heightDivisions;
    Vertex original = { 0,0,-radius };
    vector<Vertex> Cylindertop;
    //add top point into cylinder vector
    for (int i = 0; i < radialDivisions; i++)
    {
        Vertex Cylinder1 = { radius * cos(2 * PI / radialDivisions * i),radius * sin(2 * PI / radialDivisions * i),-radius };
        Cylindertop.push_back(Cylinder1);
    }
    Cylindertop.push_back(Vertex{ radius,0,-radius });
    for (int i = 0; i < radialDivisions; i++)
    {
        Vertex c1 = original;
        Vertex c2 = Cylindertop[i];
        Vertex c3 = Cylindertop[i + 1];
        C.addTriangle(c1, c2, c3);
    }
    //draw the trangle layer by layer
    for (int i = 0; i < heightDivisions; i++)
    {
        for (int j = 0; j < radialDivisions; j++) {
            Vertex temp1 = Cylindertop[j];
            Vertex temp2 = Cylindertop[j + 1];
            Vertex c1 = { temp1.x,temp1.y,temp1.z + d * i };
            Vertex c2 = { temp2.x,temp2.y,temp2.z + d * (i + 1) };
            Vertex c3 = { temp2.x,temp2.y,temp2.z + d * i };
            C.addTriangle(c1, c2, c3);
            c2 = { temp1.x,temp1.y,temp1.z + d * (i + 1) };
            c3 = { temp2.x,temp2.y,temp2.z + d * (i + 1) };
            C.addTriangle(c1, c2, c3);
        }
    }
}


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
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

    float PI = 3.1415926;
    float d = 1 / heightDivisions;
    Vertex original = { 0,0,radius };
    Vertex top = { 0,0,-radius };
    vector<Vertex> conetop;

    //add top point into cylinder vector

    for (int i = 0; i < radialDivisions; i++)
    {
        Vertex cone1 = { radius * cos(2 * PI / radialDivisions * i),radius * sin(2 * PI / radialDivisions * i),radius };
        conetop.push_back(cone1);
    }
    conetop.push_back(Vertex{ radius,0,radius });

    //draw vertical;
    for (int i = 0; i < heightDivisions; i++)
    {
        vector<Vertex> layer1;
        vector<Vertex> layer2;
        //store adjcent  layer in to vector
        for (int j = 0; j < radialDivisions; j++)
        {
            float x = conetop[j].x - top.x;
            float y = conetop[j].y - top.y;
            float z = conetop[j].z - top.z;
            Vertex temp1 = { top.x + x / heightDivisions * i ,top.y + y / heightDivisions * i ,top.z + z / heightDivisions * i };
            Vertex temp2 = { top.x + x / heightDivisions * (i + 1),top.y + y / heightDivisions * (i + 1) ,top.z + z / heightDivisions * (i + 1) };
            layer1.push_back(temp1);
            layer2.push_back(temp2);
        }
        Vertex t = layer1[0];
        layer1.push_back(t);
        t = layer2[0];
        layer2.push_back(t);
        //draw the triangle point by point
        if (i == 0) {
            //for the first layer
            for (int k = 0; k < radialDivisions; k++)
            {
                Vertex c1 = top;
                Vertex c2 = layer2[k];
                Vertex c3 = layer2[k + 1];
                C.addTriangle(c1, c2, c3);
            }
        }
        else {
            for (int k = 0; k < radialDivisions; k++)
            {
                Vertex c1 = layer1[k];
                Vertex c2 = layer2[k];
                Vertex c3 = layer2[k + 1];
                C.addTriangle(c1, c2, c3);
                c2 = layer2[k + 1];
                c3 = layer1[k + 1];
                C.addTriangle(c1, c2, c3);
            }
        }

    }
    //draw the bottom
    for (int i = 0; i < radialDivisions; i++)
    {
        Vertex c1 = original;
        Vertex c2 = conetop[i];
        Vertex c3 = conetop[i + 1];
        C.addTriangle(c1, c2, c3);
    }
}


///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices != 3 )
        slices = 3;

    if( stacks < 5 )
        stacks = 5;
    
    // YOUR IMPLEMENTATION HERE

    float PI = 3.1415926;
    float d = PI / (stacks * 2);
    Vertex original = { 0,0,0.5 };
    Vertex top = { 0,0,-0.5 };
    vector<Vertex> sphere;
    vector<Vertex> spherelayer1;
    vector<Vertex> spherelayer2;
    //draw the first semisphere
    //initialize the first layer
    for (int i = 0; i < slices; i++)
    {
        Vertex t1 = { radius * cos(2 * PI / slices * i) * sin(d),radius * sin(2 * PI / slices * i) * sin(d),radius * cos(d) };
        sphere.push_back(t1);
    }
    C.addTriangle(sphere[0], sphere[1], sphere[2]);
    spherelayer1 = sphere;
    spherelayer2 = sphere;

    //start store the adjcent layer
    for (int i = 1; i < stacks; i++)
    {
        spherelayer1.swap(spherelayer2);
        spherelayer2.clear();
        int number = slices * pow(2, i);
        for (int j = 0; j < number; j++)
        {
            Vertex t2 = { radius * cos(2 * PI / number * j) * sin(d * (i + 1)),radius * sin(2 * PI / number * j) * sin(d * (i + 1)),radius * cos(d * (i + 1)) };
            spherelayer2.push_back(t2);
        }

        for (int j = 0; j < spherelayer1.size(); j++)
        {
            Vertex s1 = spherelayer1[j];
            Vertex s2 = spherelayer2[2 * j];
            Vertex s3 = spherelayer2[2 * j + 1];
            C.addTriangle(s1, s2, s3);
            if (j == spherelayer1.size() - 1) {
                s1 = { (spherelayer1[j].x + spherelayer1[0].x) / 2,(spherelayer1[j].y + spherelayer1[0].y) / 2,(spherelayer1[j].z + spherelayer1[0].z) / 2 };
                s2 = spherelayer2[2 * j + 1];
                s3 = spherelayer2[0];
                C.addTriangle(s1, s2, s3);
            }
            else {
                s1 = { (spherelayer1[j].x + spherelayer1[j + 1].x) / 2,(spherelayer1[j].y + spherelayer1[j + 1].y) / 2,(spherelayer1[j].z + spherelayer1[j + 1].z) / 2 };
                s2 = spherelayer2[2 * j + 1];
                s3 = spherelayer2[2 * j + 2];
                C.addTriangle(s1, s2, s3);
            }
        }
    }

    //draw the second semisphere
    sphere.clear();
    spherelayer1.clear();
    spherelayer2.clear();
    for (int i = 0; i < slices; i++)
    {
        Vertex t1 = { radius * cos(2 * PI / slices * i) * sin(PI - d),radius * sin(2 * PI / slices * i) * sin(PI - d),radius * cos(PI - d) };
        sphere.push_back(t1);
    }
    C.addTriangle(sphere[0], sphere[1], sphere[2]);
    spherelayer1 = sphere;
    spherelayer2 = sphere;

    for (int i = 1; i < stacks; i++)
    {
        spherelayer1.swap(spherelayer2);
        spherelayer2.clear();
        int number = slices * pow(2, i);
        for (int j = 0; j < number; j++)
        {
            Vertex t2 = { radius * cos(2 * PI / number * j) * sin(PI - d * (i + 1)),radius * sin(2 * PI / number * j) * sin(PI - d * (i + 1)),radius * cos(PI - d * (i + 1)) };
            spherelayer2.push_back(t2);
        }

        for (int j = 0; j < spherelayer1.size(); j++)
        {
            Vertex s1 = spherelayer1[j];
            Vertex s2 = spherelayer2[2 * j];
            Vertex s3 = spherelayer2[2 * j + 1];
            C.addTriangle(s1, s2, s3);
            if (j == spherelayer1.size() - 1) {
                s1 = { (spherelayer1[j].x + spherelayer1[0].x) / 2,(spherelayer1[j].y + spherelayer1[0].y) / 2,(spherelayer1[j].z + spherelayer1[0].z) / 2 };
                s2 = spherelayer2[2 * j + 1];
                s3 = spherelayer2[0];
                C.addTriangle(s1, s2, s3);
            }
            else {
                s1 = { (spherelayer1[j].x + spherelayer1[j + 1].x) / 2,(spherelayer1[j].y + spherelayer1[j + 1].y) / 2,(spherelayer1[j].z + spherelayer1[j + 1].z) / 2 };
                s2 = spherelayer2[2 * j + 1];
                s3 = spherelayer2[2 * j + 2];
                C.addTriangle(s1, s2, s3);
            }
        }
    }
}
