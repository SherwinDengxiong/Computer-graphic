//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include <list>
#include <algorithm>
#include <iostream>
#include <math.h>

#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Simple class that performs rasterization algorithms
///

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls to the
// setPixel() function.
//
// @param n - number of vertices
// @param x - array of x coordinates
// @param y - array of y coordinates
///
void Rasterizer::drawPolygon(int n, const int x[], const int y[] )
{
    // YOUR IMPLEMENTATION HERE
    //store all the edge info
    //if(n==3){
        int oriET[n][6];
        int newET[n][6];
        int AET[n][6]={0};
        int totalymin=y[1];
        int node[6];
        //create original ET for each edge
        for (int i=0;i<n;i++){
            //this method is to create a method to create a node contain ymax x dx dy ymin from two adjcant point
            /// \param x1 first point x
            /// \param y1 first point y
            /// \param x2 second point x
            /// \param y2 second point y
            int x1=0;
            int y1=0;
            int x2=0;
            int y2=0;
            if(i!=n-1){
                x1=x[i];
                y1=y[i];
                x2=x[i+1];
                y2=y[i+1];
            } else{
                x1=x[0];
                y1=y[0];
                x2=x[i];
                y2=y[i];
            }
            int ymax=0;
            int xbottom=0;
            int dx=0;
            int dy=0;
            int ymin=0;
            int xmin=0;
            if(y1>=y2){
                ymax=y1;
                ymin=y2;
                xbottom=x2;
                dx=x1-x2;
                dy=y1-y2;
            } else{
                ymax=y2;
                ymin=y1;
                xbottom=x1;
                dx=x2-x1;
                dy=y2-y1;
            }
            if(x1>=x2){
                xmin=x2;
            } else{
                xmin=x1;
            }
            if(ymin<totalymin){
                totalymin=ymin;
            }
            oriET[i][0]=ymax;
            oriET[i][1]=xbottom;
            oriET[i][2]=ymin;
            oriET[i][3]=xmin;
            oriET[i][4]=dx;
            oriET[i][5]=dy;
        }
        ///copy oriET to new ET
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 6; ++j) {
                newET[i][j]=oriET[i][j];
            }
        }
        ///sort the newET according to its x
        for(int i=0; i<n;i++){
            int minindex=i;
            for (int index=0;index<i;index++){
                if(newET[index][2]>newET[minindex][2]) {
                    minindex = index;

                    for (int j = 0; j < 6; ++j) {
                        node[j] = newET[i][j];
                    }//copy the smaller one to temp node
                    for (int j = 0; j < 6; ++j) {
                        newET[i][j] = newET[minindex][j];
                    }
                    for (int j = 0; j < 6; ++j) {
                        newET[minindex][j] = node[j];
                    }
                }
            }
        }
        ///set the horizontal edge info to -1
        for (int i = 0; i < n; ++i) {
            if(newET[i][5]==0){
                for (int j = 0; j <6 ; ++j) {
                    newET[i][j]=-1;
                }
            } else{
                continue;
            }
        }
        /// do the AET procedure
        int count=0;
        int start=0;
        int end=0;
        int maxylist[n];
        int minylist[n];
        int AETmaxlist[n];
        int AETminlist[n];
        int minindex;
        double tempnumber;
        for (int i = 0; i < n; i++) {
            maxylist[i]=newET[i][0];
            minylist[i]=newET[i][2];
        }
        for (int i = 0; i <600; i++) {
            if(i==newET[0][2]){
                for (int j = 0; j < n; j++) {
                    if (newET[j][2]==i && newET[j][5]!=0){
                        for (int k = 0; k < 6; k++) {
                            AET[count][k]=newET[j][k];//copy newet to AET
                        }
                        count++;
                    }
                }//add first two edge to AET
                for (int j = 0; j < n; j++) {
                    AETmaxlist[j]=AET[j][0];
                    AETminlist[j]=AET[j][2];
                }
                //sort the AET
                for(int k=0; k<n;k++){
                    minindex=k;
                    for (int index=0;index<k;index++){
                        if(AET[index][0]<AET[minindex][0]) {
                            minindex = index;

                            for (int j = 0; j < 6; ++j) {
                                node[j] = AET[k][j];
                            }//copy the smaller one to temp node
                            for (int j = 0; j < 6; ++j) {
                                AET[k][j] = AET[minindex][j];
                            }
                            for (int j = 0; j < 6; ++j) {
                                AET[minindex][j] = node[j];
                            }
                        }
                    }
                }
                //check the horizontal line in the bottom
                for (int j = 0; j < n; j++) {
                    if (newET[j][5]==0){

                        start=AET[0][1];
                        end=AET[1][1];

                        for (int k = start; k < end; k++) {
                            C.setPixel(k,i);//this is to set pixel for bottom horizontal line
                        }
                        count++;
                    }
                }
                C.setPixel(AET[0][1],i);
                continue;
            }else if(i==AET[0][0]){
                ///replace the used edge with adjacent edge
                for (int j = 0; j <6 ; ++j) {
                    AET[0][j]=newET[count][j];
                }
                count++;
                ///after adding the edge sort AET according to the min x coordinate
                for(int k=0; k<n;k++){
                    minindex=k;
                    for (int index=0;index<k;index++){
                        if(AET[index][3]<AET[minindex][3]) {
                            minindex = index;

                            for (int j = 0; j < 6; ++j) {
                                node[j] = AET[k][j];
                            }//copy the smaller one to temp node
                            for (int j = 0; j < 6; ++j) {
                                AET[k][j] = AET[minindex][j];
                            }
                            for (int j = 0; j < 6; ++j) {
                                AET[minindex][j] = node[j];
                            }
                        }
                    }
                }
            } else if(i==AET[1][0]){
                for (int j = 0; j <6 ; ++j) {
                    AET[0][j]=newET[count][j];
                }
                count++;
                ///after adding the edge sort AET
                for(int k=0; k<n;k++){
                    minindex=k;
                    for (int index=0;index<k;index++){
                        if(AET[index][0]<AET[minindex][0]) {
                            minindex = index;

                            for (int j = 0; j < 6; ++j) {
                                node[j] = AET[k][j];
                            }//copy the smaller one to temp node
                            for (int j = 0; j < 6; ++j) {
                                AET[k][j] = AET[minindex][j];
                            }
                            for (int j = 0; j < 6; ++j) {
                                AET[minindex][j] = node[j];
                            }
                        }
                    }
                }
            } else{
                ///do the print
                ///for the right part edge
                tempnumber=AET[0][1]+double(AET[0][5])/double(AET[0][4]);//the current x
                end=floor(tempnumber);
                AET[0][1]=end;//put current x into edge
                ///for the left part edge
                tempnumber=AET[1][1]+double(AET[1][5])/double(AET[1][4]);
                start=floor(tempnumber);
                AET[1][1]=start;
                for (int j = start; j <end ; ++j) {
                    C.setPixel(j,i);
                }
            }
        }
    //}


}









