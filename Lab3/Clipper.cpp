//
//  Clipper.cpp
//
//  Created by Warren R. Carithers on 01/15/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include "Vertex.h"
#include "Clipper.h"
#include <iostream>
using namespace std;

///
// Simple module that performs clipping
///

///
// Constructor
///
Clipper::Clipper() {
}

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///

int Clipper::clipPolygon( int in, const Vertex inV[], Vertex outV[],
                          Vertex ll, Vertex ur )
{
    int arraylength = in;
    int count = 0;


    // YOUR CODE GOES HERE
    Vertex ul = { ll.x,ur.y };
    Vertex lr = { ur.x,ll.y };
    Vertex firstpoint;
    Vertex secondpoint;
    for (int i = 0; i < arraylength; i++)
    {
        
        if (i == arraylength - 1)
        {
            firstpoint = inV[i];
            secondpoint = inV[0];
        }
        else
        {
            firstpoint = inV[i];
            secondpoint = inV[i + 1];
        }
        if (isinside(firstpoint, ll, ur)) {
//one point inside
            if (isinside(secondpoint, ll, ur))
            {
//another point inside
                
                if (!arraycontain(outV, firstpoint,count))
                {
                    outV[count] = firstpoint;
                   
                    count++;
                    
                }
                if (!arraycontain(outV,secondpoint,count))
                {
                    outV[count] = secondpoint;
                    
                    count++;
                    
                }
            }
            else
            {
                
                secondpoint = findjunction(firstpoint, secondpoint, ll, ur);
                
                if (!arraycontain(outV, firstpoint,count))
                {
                    outV[count] = firstpoint;
                  
                    count++;
                   
                }
                if (!arraycontain(outV, secondpoint,count))
                {
                    outV[count] = secondpoint;
                   
                    count++;
                    
                }

            }
        }
        else
        {
            if (isinside(secondpoint, ll, ur))
            {
                
                firstpoint = findjunction(firstpoint, secondpoint, ll, ur);
                
                if (!arraycontain(outV, firstpoint,count))
                {
                    outV[count] = firstpoint;
                    
                    count++;
                    
                }
                if (!arraycontain(outV, secondpoint,count))
                {
                    outV[count] = secondpoint;
                    
                    count++;
                  
                }
            }
            else
            {
//two point outside
                
                if (outsideclip(firstpoint, secondpoint, ll, ur))
                {
                    
                        Vertex corner = whichconer(firstpoint, secondpoint, ll, ur, in);
                   
                    
                    if (!arraycontain(outV, corner, count))
                    {
                        if (in <= 4) {
                            continue;
                        }if (in == 9) {
                            continue;
                        }
                        else {
                            outV[count] = corner;
                            count++;
                        }
                        
                    }
                }

            }
        }


    }

    if (in == 9) {
        
        outV[count] = ll;
        count++;
        outV[count] = ul;
        count++;
        outV[count] = lr;
        count++;
        outV[count] = ur;
        count++;
        


    }
    
    return count;  // remember to return the outgoing vertex count!

}
Vertex Clipper::whichconer(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur,int n) 
{//area of outside point
//return the corner point
    
    Vertex llpoint;
    Vertex urpoint;
    if (firstpoint.x < secondpoint.x)
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = firstpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = firstpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
    else
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = secondpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = secondpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
    Vertex ul = { ll.x,ur.y };
    Vertex lr = { ur.x,ll.y };
    Vertex A = lr;
    if (llpoint.x<ll.x && urpoint.x>ll.x)
    {
        A = ll;
    }
    else if(llpoint.y<ll.y && urpoint.y>ll.y)
    {
        A = ll;
    }
    if (llpoint.x<ul.x && urpoint.x>ul.x)
    {
        A = ul;
    }
    else if (llpoint.y<ul.y && urpoint.y>ul.y)
    {
        A = ul;
    }
    if (llpoint.x<lr.x && urpoint.x>lr.x)
    {
        A = lr;
    }
    else if (llpoint.y<lr.y && urpoint.y>lr.y)
    {
        A = lr;
    }
    if (llpoint.x<ur.x && urpoint.x>ur.x)
    {
        A = ur;
    }
    else if (llpoint.y<ur.y && urpoint.y>ur.y)
    {
        A = ur;
    }
    Vertex B = ll;
    if (n == 5) 
    {
        B = ll;
    
    }
    else if (n==7)
    {
        B = lr;
    }
    else if (n == 10)
    {
        B = ll;
    }
    return B;

}
bool Clipper::arraycontain(const Vertex inV[], Vertex temp,int count)
{
  //test whether array contain vertex
    for (int i = 0; i < count+1; i++)
    {
        if (inV[i].x == temp.x && inV[i].y == temp.y)
        {
            return true;
        }
    }
    return false;
}
bool Clipper::outsideclip(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur)
{
    //area of outside point
    Vertex llpoint;
    Vertex urpoint;
    if (firstpoint.x < secondpoint.x)
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = firstpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = firstpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
    else
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = secondpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = secondpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
    //calculate the 4 junction point
    double m = (firstpoint.y - secondpoint.y) / (firstpoint.x - secondpoint.x);
    double b = firstpoint.y - m * firstpoint.x;
    Vertex temparry[4];
    Vertex temp1;
    Vertex temp2;
    Vertex temp3;
    Vertex temp4;
    temp1.x = ll.x;
    temp1.y = m * temp1.x + b;
    temparry[0] = temp1;
    temp2.x = ur.x;
    temp2.y = m * temp2.x + b;
    temparry[1] = temp2;
    temp3.y = ll.y;
    temp3.x = (temp3.y - b) / m;
    temparry[2] = temp3;
    temp4.y = ur.y;
    temp4.x = (temp4.y - b) / m;
    temparry[3] = temp4;
    for (int i = 0; i < 4; i++)
    {
        if (isinside(temparry[i], llpoint, urpoint))
        {
            if (isinside(temparry[i], ll, ur))
            {
                return false;
            }
        }
    }
    
    return true;

}

Vertex Clipper::findjunction(Vertex firstpoint, Vertex secondpoint, Vertex ll, Vertex ur)
{
    //retrun the junction of the edge
    Vertex llpoint;
    Vertex urpoint;
    //area of outside point
    if (firstpoint.x < secondpoint.x)
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = firstpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = firstpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = secondpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
    else
    {
        if (firstpoint.y < secondpoint.y)
        {
            llpoint.x = secondpoint.x;
            llpoint.y = firstpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = secondpoint.y;
        }
        else
        {
            llpoint.x = secondpoint.x;
            llpoint.y = secondpoint.y;
            urpoint.x = firstpoint.x;
            urpoint.y = firstpoint.y;
        }
    }
 //calculate the four junction points
    double m = (firstpoint.y - secondpoint.y) / (firstpoint.x - secondpoint.x);
    double b = firstpoint.y - m * firstpoint.x;
    Vertex temparry[4];
    Vertex temp1;
    Vertex temp2;
    Vertex temp3;
    Vertex temp4;
    temp1.x = ll.x;
    temp1.y = m * temp1.x + b;
    temparry[0] = temp1;
    temp2.x = ur.x;
    temp2.y = m * temp2.x + b;
    temparry[1] = temp2;
    temp3.y = ll.y;
    temp3.x = (temp3.y - b) / m;
    temparry[2] = temp3;
    temp4.y = ur.y;
    temp4.x = (temp4.y - b) / m;
    temparry[3] = temp4;
    for (int i = 0; i < 4; i++)
    {
        if (isinside(temparry[i], llpoint,urpoint))
        {
            if (isinside(temparry[i], ll, ur))
            {
//find the correct junction point
                return temparry[i];
            }
        }
    }


}
bool Clipper::isinside(Vertex v, Vertex ll, Vertex ur)
{
    //judge the vertex is inside the clipper area
    if (v.x <= ur.x && v.x >= ll.x && v.y <= ur.y && v.y >= ll.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
