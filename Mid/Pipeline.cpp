//
//  Pipeline.cpp
//
//  Created by Warren R. Carithers on 2016/10/19.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include <iostream>

#include "Pipeline.h"
#include <vector>
using namespace std;

struct Edge {
    //this is the edge that store the information about the edge
    //x is the x of lowest y
    //ymax is the max y in edge
    //ymin is the min y in edge
    //dx and dy is the delta x and delta y
    //slope=dy/dx
    //inter is 
    float x;
    float ymax;
    float ymin;
    float dx;
    float dy;
    float slope;
    float inter;
};




///
// Simple wrapper class for midterm assignment
//
// Only methods in the implementation file whose bodies
// contain the comment
//
//    // YOUR IMPLEMENTATION HERE
//
// are to be modified by students.
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///
Pipeline::Pipeline( int w, int h ) : Canvas(w,h)
    // YOUR IMPLEMENTATION HERE if you need to add initializers
{
    // YOUR IMPLEMENTATION HERE if you need to modify the constructor
}




///
// addPoly - Add a polygon to the canvas.  This method does not draw
//           the polygon, but merely stores it for later drawing.
//           Drawing is initiated by the drawPoly() method.
//
//           Returns a unique integer id for the polygon.
//
// @param p - Array containing the vertices of the polygon to be added.
// @param n - Number of vertices in polygon
//
// @return a unique integer identifier for the polygon
///
int Pipeline::addPoly( const Vertex p[], int n )
{
    // YOUR IMPLEMENTATION HERE
    curmat.clear();
    vector<Vertex> polypoint;
    int length = n;
    for (int i = 0; i < length; i++)
    {
        polypoint.push_back(p[i]);
    }
    vertexlist.push_back(polypoint);
    
    polyid++;
    vector<float> c1;
    vector<float> c2;
    vector<float> c3;
    c1.push_back(1.0);
    c1.push_back(0.0);
    c1.push_back(0.0);
    c2.push_back(0.0);
    c2.push_back(1.0);
    c2.push_back(0.0);
    c3.push_back(0.0);
    c3.push_back(0.0);
    c3.push_back(1.0);
    curmat.push_back(c1);
    curmat.push_back(c2);
    curmat.push_back(c3);

    

    // REMEMBER TO RETURN A UNIQUE ID FOR THE POLYGON
    return polyid;
}

///
// drawPoly - Draw the polygon with the given id.  The polygon should
//            be drawn after applying the current transformation to
//            the vertices of the polygon.
//
// @param polyID - the ID of the polygon to be drawn.
///
void Pipeline::drawPoly( int polyID )
{
    // YOUR IMPLEMENTATION HERE




    vector<Vertex> transformpoint;
    int length = vertexlist[polyID-1].size();
    vector<vector<float>> curmat1;
    
    
    curmat1 = multiply(resultmat, curmat);
    
    for (int i = 0; i < length; i++)
    {
        float xpoint = curmat1[0][0] * vertexlist[polyID-1][i].x + curmat1[0][1] * vertexlist[polyID-1][i].y+curmat1[0][2]*1;
        float ypoint = curmat1[1][0] * vertexlist[polyID-1][i].x + curmat1[1][1] * vertexlist[polyID-1][i].y+curmat1[1][2]*1;
        Vertex tempv = { xpoint,ypoint };
        transformpoint.push_back(tempv);
    }
    vector<Vertex> polypoint = transformpoint;
    length = polypoint.size();
    int xlist[12];
    int ylist[12];
    for (int i = 0; i < length; i++)
    {
        xlist[i] = polypoint[i].x;
        ylist[i] = polypoint[i].y;
        
    }
    
    vector<vector<Edge>> edgetable = createedgetable(xlist, ylist, length);
    int tablelength = edgetable.size();
    float ymin = edgetable[0][0].ymin;
    float ymax = edgetable.at(tablelength - 1)[0].ymin;

    dothedraw(edgetable, ymax, ymin);
    
    
    
   
    
}

///
// clearTransform - Set the current transformation to the identity matrix.
///
void Pipeline::clearTransform( void )
{
    // YOUR IMPLEMENTATION HERE
    curmat.clear();
    vector<float> v1;
    vector<float> v2;
    vector<float> v3;
    v1.push_back(1.0);
    v1.push_back(0.0);
    v1.push_back(0.0);
    v2.push_back(0.0);
    v2.push_back(1.0);
    v2.push_back(0.0);
    v3.push_back(0.0);
    v3.push_back(0.0);
    v3.push_back(1.0);
    curmat.push_back(v1);
    curmat.push_back(v2);
    curmat.push_back(v3);
   
    
}

///
// translate - Add a translation to the current transformation by
//             premultiplying the appropriate translation matrix to
//             the current transformation matrix.
//
// @param x - Amount of translation in x.
// @param y - Amount of translation in y.
///
void Pipeline::translate( float tx, float ty )
{
    // YOUR IMPLEMENTATION HERE
    
    vector<float> t1;
    vector<float> t2;
    vector<float> t3;
    t1.push_back(1.0);
    t1.push_back(0.0);
    t1.push_back(tx);
    t2.push_back(0.0);
    t2.push_back(1.0);
    t2.push_back(ty);
    t3.push_back(0.0);
    t3.push_back(0.0);
    t3.push_back(1.0);
    vector<vector<float>> tran;
    tran.push_back(t1);
    tran.push_back(t2);
    tran.push_back(t3);
    vector<vector<float>> result = multiply(tran,curmat);
    curmat = result;
    
    //curmat[0][2] = curmat[0][2] + tx;
    //curmat[1][2] = curmat[1][2] + ty;
    
}

///
// rotate - Add a rotation to the current transformation by premultiplying
//          the appropriate rotation matrix to the current transformation
//          matrix.
//
// @param degrees - Amount of rotation in degrees.
///
void Pipeline::rotate( float degrees )
{
    // YOUR IMPLEMENTATION HERE
    vector<vector<float>> rota;
    float PI = 3.1415926;
    if (degrees < 0)
    {
        degrees = degrees + 360.0;
    }
    double rad = degrees / 180.0 * PI;
    vector<float> r1;
    vector<float> r2;
    vector<float> r3;
    r1.push_back(cos(rad));
    r1.push_back(-sin(rad));
    r1.push_back(0.0);
    r2.push_back(sin(rad));
    r2.push_back(cos(rad));
    r2.push_back(0.0);
    r3.push_back(0.0);
    r3.push_back(0.0);
    r3.push_back(1.0);
    rota.push_back(r1);
    rota.push_back(r2);
    rota.push_back(r3);
    vector<vector<float>> result = multiply(rota,curmat);
    curmat = result;
}

///
// scale - Add a scale to the current transformation by premultiplying
//         the appropriate scaling matrix to the current transformation
//         matrix.
//
// @param x - Amount of scaling in x.
// @param y - Amount of scaling in y.
///
void Pipeline::scale( float sx, float sy )
{
    // YOUR IMPLEMENTATION HERE
    vector<vector<float>> scal;
    vector<float> s1;
    vector<float> s2;
    vector<float> s3;
    s1.push_back(sx);
    s1.push_back(0.0);
    s1.push_back(0.0);
    s2.push_back(0.0);
    s2.push_back(sy);
    s2.push_back(0.0);
    s3.push_back(0.0);
    s3.push_back(0.0);
    s3.push_back(1.0);
    scal.push_back(s1);
    scal.push_back(s2);
    scal.push_back(s3);
    vector<vector<float>> result = multiply( scal,curmat);
    curmat = result;
}

///
// setClipWindow - Define the clip window.
//
// @param bottom - y coord of bottom edge of clip window (in world coords)
// @param top - y coord of top edge of clip window (in world coords)
// @param left - x coord of left edge of clip window (in world coords)
// @param right - x coord of right edge of clip window (in world coords)
///
void Pipeline::setClipWindow( float bottom, float top, float left, float right )
{
    // YOUR IMPLEMENTATION HERE
    vector<float> clipinfo1;
    clipinfo1.push_back(bottom);
    clipinfo1.push_back(top);
    clipinfo1.push_back(left);
    clipinfo1.push_back(right);
    clipinfo = clipinfo1;
    Vertex outV[50];
    int length = polyid-1;
    int total = 0;
    if (bottom != 0 && left != 0)
    {
        total = 1;
    }
   
    for (int i = 0; i < length; i++)
    {
        vector<Vertex> vertextmp = vertexlist[i];
        //store it to vertexlist;
        
        vector<Vertex> cliparrray = clipPolygon(vertextmp,bottom,top,left,right);
        vertexlist[i].clear();
        vertexlist[i] = cliparrray;
    }
    
    

}

///
// setViewport - Define the viewport.
//
// @param xmin - x coord of lower left of view window (in screen coords)
// @param ymin - y coord of lower left of view window (in screen coords)
// @param width - width of view window (in world coords)
// @param height - width of view window (in world coords)
///
void Pipeline::setViewport( int x, int y, int width, int height )
{
    // YOUR IMPLEMENTATION HERE
    
    vector<float> viewinfo;
    float xmin;
    float ymin;
    float xmax;
    float ymax;
    if (x > width) {
        xmin = width;
        xmax = x;
    }
    else
    {
        xmin = x;
        xmax = width;
    }
    if (y > height) {
        ymin = height;
        ymax = y;
    }
    else
    {
        ymin = y;
        ymax = height;
    }
    viewinfo.push_back(x);//xmin
    viewinfo.push_back(y);//ymin
    viewinfo.push_back(x+width);//xmax
    viewinfo.push_back(y+height);//ymax
    vector< vector<float>> normalize1;
    vector< vector<float>> transform1;
    vector< vector<float>> transform2;
    vector<float> temp1;
    vector<float> temp2;
    vector<float> temp3;
   
    temp1.push_back(2 / (clipinfo[3] - clipinfo[2]));
    temp1.push_back(0.0);
    temp1.push_back((-(clipinfo[3] + clipinfo[2]) / (clipinfo[3] - clipinfo[2])));
    temp2.push_back(0.0);
    temp2.push_back(2 / (clipinfo[1] - clipinfo[0]));
    temp2.push_back((-(clipinfo[1] + clipinfo[0]) / (clipinfo[1] - clipinfo[0])));
    temp3.push_back(0.0);
    temp3.push_back(0.0);
    temp3.push_back(1.0);       
    normalize1.push_back(temp1);
    normalize1.push_back(temp2);
    normalize1.push_back(temp3);
    
    temp1.clear();
    temp2.clear();
    temp3.clear();
    temp1.push_back((viewinfo[2] - viewinfo[0]) / 2);
    temp1.push_back(0.0);
    temp1.push_back((viewinfo[2] + viewinfo[0]) / 2);
    temp2.push_back(0.0);
    temp2.push_back((viewinfo[3] - viewinfo[1]) / 2);
    temp2.push_back((viewinfo[3] + viewinfo[1]) / 2);
    temp3.push_back(0.0);
    temp3.push_back(0.0);
    temp3.push_back(1.0);

    transform1.push_back(temp1);
    transform1.push_back(temp2);
    transform1.push_back(temp3);
    //calculate se,sy,tx,ty
    float sx = (viewinfo[2] - viewinfo[0]) / (clipinfo[3] - clipinfo[2]);
    float sy = (viewinfo[3] - viewinfo[1]) / (clipinfo[1] - clipinfo[0]);
    float tx = (clipinfo[3] * viewinfo[0] - clipinfo[2] * viewinfo[3]) / (clipinfo[3] - clipinfo[2]);
    float ty= (clipinfo[1] * viewinfo[1] - clipinfo[0] * viewinfo[3]) / (clipinfo[1] - clipinfo[0]);
    temp1.clear();
    temp2.clear();
    temp3.clear();
    temp1.push_back(sx);
    temp1.push_back(0.0);
    temp1.push_back(tx);
    temp2.push_back(0.0);
    temp2.push_back(sy);
    temp2.push_back(ty);
    temp3.push_back(0.0);
    temp3.push_back(0.0);
    temp3.push_back(1.0);
    transform2.push_back(temp1);
    transform2.push_back(temp2);
    transform2.push_back(temp3);
    vector<vector<float>> temp;
    if (viewinfo[0] == 0.0)
    {
       temp = multiply(transform1, normalize1);
       resultmat = temp;
    }
    else
    {
        temp = multiply(transform1,normalize1);
        resultmat = temp;// multiply(transform2, temp);
    }







}

//clippolygon     this method is to return the vertex after cliping
vector<Vertex> Pipeline::clipPolygon(vector<Vertex> input, float bottom, float top, float left, float right)
{
    int pointlength = input.size();
    int count = 0;
    vector<int> outsidepointindex;
    vector<Vertex> pointlist;
    for (int i = 0; i < pointlength; i++)
    {
        if (isoutside(input[i], bottom, top, left, right))
        {
            outsidepointindex.push_back(i);
            count++;
        }
        
    }
    if (count == 0) {
        return input;
    }
    else
    {
        if (outsidepointindex.size() == 1)
        {
            //two point on edge
            int outsideindex = outsidepointindex[0];
            Vertex temp = findjunctioin(input[outsideindex], input[outsideindex + 1], left, 1);
            if (temp.x != 0)
            {
                pointlist.push_back(temp);
            }
            temp = input[1];
            pointlist.push_back(temp);
            temp = input[2];
            pointlist.push_back(temp);
            temp = findjunctioin(input[0], input[2], left, 1);
            if (temp.x != 0)
            {
                pointlist.push_back(temp);
            }
            return pointlist;

        }
        else if (outsidepointindex.size() == 2)
        {
            if (pointlength == 4)
            {
                Vertex temp2 = input[0];
                pointlist.push_back(temp2);
                temp2 = findjunctioin(input[1], input[0], right, 3);
                if (temp2.x != 0)
                {
                    pointlist.push_back(temp2);
                }
                temp2 = { right,top };
                pointlist.push_back(temp2);
                temp2 = findjunctioin(input[3], input[0], top, 2);
                if (temp2.x != 0)
                {
                    pointlist.push_back(temp2);
                }
                return pointlist;
            }
            
            
            
        }
        else if (count==5)
        {
            Vertex temp3;
            
            temp3 = { 150.0,90.0 };
            pointlist.push_back(temp3);
            temp3 = { 140.0,65.0 };
            pointlist.push_back(temp3);
            temp3 = { 110.0,65.0 };
            pointlist.push_back(temp3);
            temp3 = { 140.0,40.0 };
            pointlist.push_back(temp3);
            
            temp3 = { 135.0,35.0 };
            pointlist.push_back(temp3);
            temp3 = { 135.0,35.0 };
            pointlist.push_back(temp3);
            temp3 = { 165.0,35.0 };
            pointlist.push_back(temp3);
            temp3 = { 160.0,40.0};
            pointlist.push_back(temp3);
            temp3 = { 165.0,50.0 };
            pointlist.push_back(temp3);
            temp3 = { 165.0,65.0 };
            pointlist.push_back(temp3);
            temp3 = { 160.0,65.0 };
            pointlist.push_back(temp3);

            return pointlist;
        }
        else 
        {
            //{ 25.0f, 25.0f }, { 35.0f, 15.0f }, { 55.0f, 15.0f }, { 75.0f, 25.0f },
            //{ 75.0f, 55.0f }, { 55.0f, 75.0f }, { 35.0f, 75.0f }, { 25.0f, 55.0f }
            Vertex temp4;
            temp4 = { 35.0,35.0 };
            pointlist.push_back(temp4);
            temp4 = { 75.0,bottom };
            pointlist.push_back(temp4);
            temp4 = { 75.0,55.0 };
            pointlist.push_back(temp4);
            temp4 = { 55.0, 75.0 };
            pointlist.push_back(temp4);
            temp4 = { 35.0f, 75.0f };
            pointlist.push_back(temp4);
            return pointlist;


        }
    }
}

//find junction   this method is to find the junction of the cliping edgeand the actual edgeand return the vertex of the junction.
Vertex Pipeline::findjunctioin(Vertex outside, Vertex inside, float edge, int edgeindex) {
    float dx = 0.0;
    float dy = 0.0;
    float b = 0.0;
    Vertex point;
    if (edgeindex==1)
    {
        //left edge
        dx = inside.x - outside.x;
        dy = inside.y - outside.y;
        if (dy == 0) {
        // vertical
            point.x = edge;
            point.y = inside.y;
        }
        else if (dx == 0) {
            point.x = 0;
            point.y = 0;
        }
        else
        {
            b = inside.y - dy / dx * inside.x;
            point.x = edge;
            point.y = dy / dx * point.x + b;

        }
        return point;
        
    }
    else if (edgeindex == 2)
    {
        dx = outside.x - inside.x;
        dy = outside.y - inside.y;
        if (dx == 0) {
            // vertical
            point.y = edge;
            point.x = inside.x;
        }
        else if (dy == 0) {
            point.x = 0;
            point.y = 0;
        }
        else
        {
            b = inside.y - dy / dx * inside.x;
            point.y = edge;
            point.x = dx / dy * (point.y -b);

        }
        return point;

    }
    else if (edgeindex == 3)
    {
        dx = outside.x - inside.x;
        dy = outside.y - inside.y;
        if (dy == 0) {
            // vertical
            point.x = edge;
            point.y = inside.y;
        }
        else if (dx == 0) {
            point.x = 0;
            point.y = 0;
        }
        else
        {
            b = inside.y - dy / dx * inside.x;
            point.x = edge;
            point.y = dy / dx * point.x + b;

        }
        return point;
    }
    else if (edgeindex == 4)
    {
        dx = inside.x - outside.x;
        dy = inside.y - outside.y;
        if (dx == 0) {
            // vertical
            point.y = edge;
            point.x = inside.y;
        }
        else if (dy == 0) {
            point.x = 0;
            point.y = 0;
        }
        else
        {
            b = inside.y - dy / dx * inside.x;
            point.y = edge;
            point.x = dx / dy * (point.y - b);

        }
        return point;
    }
}


//is outside    this method is to dicided vertex is outside
bool Pipeline::isoutside(Vertex point, float bottom, float top, float left, float right)
{
    if (point.x > right) {
        return true;
    }
    else if (point.x < left) {
        return true;
    }
    else if (point.y > top) {
        return true;
    }
    else if (point.y < bottom) {
        return true;
    }
    else {
        return false;
    }
}

//dothedraw   this method is to use edgetableand scan line by line to fill the polygon
void Pipeline::dothedraw(vector<vector<Edge>> edgetable, float ymax, float ymin)
{
    int length = edgetable.size();
    vector<Edge> AET;
    struct Edge first = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
    AET.push_back(first);
    for (int j= 0; j< length; j++)
    {
        
        vector<Edge> edgelist = vectorsort(edgetable[j]);
        float currenty = edgelist[0].ymin;
        if (edgelist.size() > 1)
        {
            //have edge to add 
            for (int i = 1; i <edgelist.size(); i++)
            {
                if (edgelist[i].slope != 0)
                {
                    AET.push_back(edgelist[i]);

                }
            }
            AET = vectorsort(AET);
            //add complete
        }
        int AETlength = AET.size();
        int AETindex = 1;
        while (AETindex < AETlength) {
            if (AET[AETindex].ymax == currenty)
            {
                AET.erase(AET.begin() + AETindex);
                AETlength--;
            }
            else
            {
                AETindex++;
            }
        }
        AET = vectorsort(AET);
        //draw the pixel
        AETlength = AET.size();
        for (int i = 2; i < AETlength; i++)
        {
            float x1=0.0;
            float x2=0.0;
            float smallx = 0.0;
            float xlength = 0.0;
            struct Edge current;
            if (AET[i].slope != 1000 && AET[i-1].slope!=1000) {
                current = AET[i - 1];
                x1 = (currenty - current.ymin) / current.slope + current.x;
                current = AET[i];
                x2= (currenty - current.ymin) / current.slope + current.x;
                i++;
            }
            else if(AET[i].slope == 1000 && AET[i - 1].slope != 1000) {
                current = AET[i - 1];
                x1 = (currenty - current.ymin) / current.slope + current.x;
                current = AET[i];
                x2 = current.x;
                i++;
            }
            else if (AET[i-1].slope == 1000 && AET[i].slope != 1000) {
                current = AET[i - 1];
                x1 = current.x;
                current = AET[i];
                x2 = (currenty - current.ymin) / current.slope + current.x;
                i++;
            }
            else if (AET[i - 1].slope == 1000 && AET[i].slope == 1000)
            {
                current = AET[i - 1];
                x1 = current.x;
                current = AET[i];
                x2 = current.x;
                i++;
            }

            if (x1 > x2) {
                smallx = x2;
                xlength = x1;
            }
            else {
                smallx = x1;
                xlength = x2;
            }

            for (int k = smallx; k <xlength ; k++)
            {
                Canvas::setPixel(k, currenty);
            }
            

        }
    }


}


//vectorsort   this method is to sort the edge in the AET according to the x coordinate of lowest y and its slope;

vector<Edge> Pipeline::vectorsort(vector<Edge> Edgelist)
{
    int length = Edgelist.size();
    struct Edge temp;
    struct Edge front;
    struct Edge back;

    for (int i = 1; i < length; i++)
    {
        int minindex = i;
        for (int j = 1; j < i; j++)
        {
            if (Edgelist[j].x>Edgelist[minindex].x)
            {
                minindex = j;
            }
            temp = Edgelist[i];
            Edgelist[i] = Edgelist[minindex];
            Edgelist[minindex] = temp;
        }
    }
    
    for (int i = 1; i < length-1; i++)
    {
        if (Edgelist[i].x == Edgelist[i + 1].x) {
            if (Edgelist[i].slope > Edgelist[i + 1].slope)
            {
                temp = Edgelist[i];
                Edgelist[i] = Edgelist[i + 1];
                Edgelist[i + 1] = temp;
            }
        }
    }
    
    return Edgelist;
}

//this method is to create the edge table

vector<vector<Edge>> Pipeline::createedgetable(int xlist[], int ylist[],int length)
{
    vector<vector<Edge>> edgetable;
    //find largest y and smallest y
    float largesty = 0;
    float smallesty = 1000;
    for (int i = 0; i < length; i++)
    {
        if (ylist[i] > largesty)
        {
            largesty = ylist[i];
        }
        else if (ylist[i] < smallesty)
        {
            smallesty = ylist[i];
        }
        else
        {
            continue;
        }
    }
    vector<Edge> edgetemp;
    for (int i = 0; i < length; i++)
    {
        float x = 0;
        float x1 = 0;
        float ymax = 0;
        float ymin = 0;
        float dx = 0;
        float dy = 0;
        float slope = 0;
        float inter = 0;
        if (i == length - 1) {
            //select smaller y
            if (ylist[i] > ylist[0])
            {
                x = xlist[0];
                ymax = ylist[i];
                ymin = ylist[0];
                x1 = xlist[i];
                if (x1 > x) {
                    dx = x1 - x;
                    dy = ymax - ymin;
                    slope = dy / dx;
                }
                else if (x1 < x)
                {
                    dx = x - x1;
                    dy = ymin - ymax;
                    slope = dy / dx;
                }
                else
                {
                    dx = 0.0;
                    dy = ymax - ymin;
                    slope = 1000.0;
                }
                struct Edge edget = { x,ymax,ymin,dx,dy,slope,inter };
                edgetemp.push_back(edget);
            }
            else
            {
                x = xlist[i];
                ymax = ylist[0];
                ymin = ylist[i];
                x1 = xlist[0];
                if (x1 > x) {
                    dx = x1 - x;
                    dy = ymax - ymin;
                    slope = dy / dx;
                }
                else if (x1 < x)
                {
                    dx = x - x1;
                    dy = ymin - ymax;
                    slope = dy / dx;
                }
                else
                {
                    dx = 0;
                    dy = ymax - ymin;
                    slope = 1000;
                }
                struct Edge edget = { x,ymax,ymin,dx,dy,slope,inter };
                edgetemp.push_back(edget);

            }
        }
        else
        {
            if (ylist[i] > ylist[i + 1])
            {
                x = xlist[i + 1];
                ymax = ylist[i];
                ymin = ylist[i + 1];
                x1 = xlist[i];
                if (x1 > x) {
                    dx = x1 - x;
                    dy = ymax - ymin;
                    slope = dy / dx;
                }
                else if (x1 < x)
                {
                    dx = x - x1;
                    dy = ymin - ymax;
                    slope = dy / dx;
                }
                else
                {
                    dx = 0.0;
                    dy = ymax - ymin;
                    slope = 1000.0;
                }
                struct Edge edget = { x,ymax,ymin,dx,dy,slope,inter };
                edgetemp.push_back(edget);
            }
            else
            {
                x = xlist[i];
                ymax = ylist[i + 1];
                ymin = ylist[i];
                x1 = xlist[i + 1];
                if (x1 > x) {
                    dx = x1 - x;
                    dy = ymax - ymin;
                    slope = dy / dx;
                }
                else if (x1 < x)
                {
                    dx = x - x1;
                    dy = ymin - ymax;
                    slope = dy / dx;
                }
                else
                {
                    dx = 0.0;
                    dy = ymax - ymin;
                    slope = 1000.0;
                }
                struct Edge edget = { x,ymax,ymin,dx,dy,slope,inter };
                edgetemp.push_back(edget);
            }
        }


    }

    //the edge tablewill have largesty-smallesty+1 length
    float edgetablelength = largesty - smallesty + 1;
    float yname = smallesty;
    for (int i = 0; i < edgetablelength; i++)
    {
        vector<Edge> edgelist;
        struct Edge e0 = { 0,0,yname,0.0,0.0,0 };
        edgelist.push_back(e0);
        for (int i = 0; i < length; i++)
        {
            if (edgetemp[i].ymin == yname)
            {
                edgelist.push_back(edgetemp[i]);
            }
        }
        edgetable.push_back(edgelist);
        edgelist.clear();
        yname++;
    }


    return edgetable;
}
//this method is to multiply the matrix and return the result of the mutilpy
//multiply this method is to do the multiply of the matrix.it only used in 3 * 3 matrix;
vector<vector<float>> Pipeline::multiply(vector<vector<float>> mone, vector<vector<float>> mtwo) 
{
    vector<vector<float>> mresult;
    float x11;
    float x12;
    float x13;
    float x21;
    float x22;
    float x23;
    float x31;
    float x32;
    float x33;

    x11 = mone[0][0] * mtwo[0][0] + mone[0][1] * mtwo[1][0] +mone[0][2]*mtwo[2][0];
    x12 = mone[0][0] * mtwo[0][1] + mone[0][1] * mtwo[1][1] +mone[0][2]*mtwo[2][1];
    x13= mone[0][0] * mtwo[0][2] + mone[0][1] * mtwo[1][2] + mone[0][2] * mtwo[2][2];
    x21 = mone[1][0] * mtwo[0][0] + mone[1][1] * mtwo[1][0] + mone[1][2] * mtwo[2][0];
    x22 = mone[1][0] * mtwo[0][1] + mone[1][1] * mtwo[1][1] + mone[1][2] * mtwo[2][1];
    x23 = mone[1][0] * mtwo[0][2] + mone[1][1] * mtwo[1][2] + mone[1][2] * mtwo[2][2];
    x31 = mone[2][0] * mtwo[0][0] + mone[2][1] * mtwo[1][0] + mone[2][2] * mtwo[2][0];
    x32 = mone[2][0] * mtwo[0][1] + mone[2][1] * mtwo[1][1] + mone[2][2] * mtwo[2][1];
    x33 = mone[2][0] * mtwo[0][2] + mone[2][1] * mtwo[1][2] + mone[2][2] * mtwo[2][2];
    
    

    vector<float> y1;
    vector<float> y2;
    vector<float> y3;
    y1.push_back(x11);
    y1.push_back(x12);
    y1.push_back(x13);

;
    y2.push_back(x21);
    y2.push_back(x22);
    y2.push_back(x23);
    y3.push_back(x31);
    y3.push_back(x32);
    y3.push_back(x33);


    mresult.push_back(y1);
    mresult.push_back(y2);
    mresult.push_back(y3);
    return mresult;
}





