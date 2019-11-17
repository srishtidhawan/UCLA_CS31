//
//  grid.cpp
//  HelloThree
//
//  Created by Srishti Dhawan on 5/1/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#include "grid.h"

#include "grid.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

bool grid[MAXROWS][MAXCOLS];  // true means wall, false means empty
int nRows = 0;
int nCols;

void doDraw(int rStart, int cStart, int rEnd, int cEnd, int rCar, int cCar);
void checkPos(int r, int c, string func);

void setSize(int nr, int nc)
{
    if (nr < 1  ||  nr > MAXROWS)
    {
        cerr << "setSize: invalid number of rows " << nr << endl;
        exit(1);
    }
    if (nc < 1  ||  nc > MAXCOLS)
    {
        cerr << "setSize: invalid number of columns " << nc << endl;
        exit(1);
    }
    nRows = nr;
    nCols = nc;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            grid[r][c] = false;
}

int getRows()
{
    if (nRows == 0)
    {
        cerr << "getRows: You must first call setSize." << endl;
        exit(1);
    }
    return nRows;
}

int getCols()
{
    if (nRows == 0)
    {
        cerr << "getCols: You must first call setSize." << endl;
        exit(1);
    }
    return nCols;
}

void setWall(int r, int c)
{
    checkPos(r, c, "setWall");
    grid[r-1][c-1] = true;
}

bool isWall(int r, int c)
{
    checkPos(r, c, "isWall");
    return grid[r-1][c-1];
}

void draw(int rStart, int cStart, int rEnd, int cEnd)
{
    checkPos(rStart, cStart, "draw");
    checkPos(rEnd, cEnd, "draw");
    doDraw(rStart, cStart, rEnd, cEnd, 0, 0);
}

void draw(int rStart, int cStart, int rEnd, int cEnd, int rCar, int cCar)
{
    checkPos(rStart, cStart, "draw");
    checkPos(rEnd, cEnd, "draw");
    checkPos(rCar, cCar, "draw");
    doDraw(rStart, cStart, rEnd, cEnd, rCar, cCar);
}

void doDraw(int rStart, int cStart, int rEnd, int cEnd, int rCar, int cCar)
{
    // Write header lines of column numbers
    
    if (nCols >= 10)
    {
        cerr << "   ";
        for (int c = 1; c <= nCols; c++)
        {
            int t = c / 10;
            if (t == 0)
                cerr << ' ';
            else
                cerr << t;
        }
        cerr << endl;
    }
    cerr << "   ";
    for (int c = 1; c <= nCols; c++)
        cerr << (c%10);
    cerr << endl;
    
    // Draw grid
    
    for (int r = 1; r <= nRows; r++)
    {
        cerr << setw(2) << r << ' ';
        for (int c = 1; c <= nCols; c++)
        {
            char ch = '.';
            if (isWall(r, c))
                ch = '*';
            if (r == rStart  &&  c == cStart)
                ch = 'S';
            else if (r == rEnd  &&  c == cEnd)
                ch = 'E';
            else if (r == rCar  &&  c == cCar)
                ch = 'C';
            cerr << ch;
        }
        cerr << endl;
    }
}

void checkPos(int r, int c, string func)
{
    if (nRows == 0)
    {
        cerr << func << ": You must first call setSize." << endl;
        exit(1);
    }
    if (r < 1  ||  r > nRows  ||  c < 1  ||  c > nCols)
    {
        cerr << func << ": invalid position (" << r << "," << c << ")"
        << endl;
        exit(1);
    }
}
