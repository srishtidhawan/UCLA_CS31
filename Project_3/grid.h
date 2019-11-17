//
//  grid.hpp
//  HelloThree
//
//  Created by Srishti Dhawan on 5/1/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>

#endif /* grid_hpp */

// Grid library interface

#ifndef GRID_INCLUDED
#define GRID_INCLUDED

const int MAXROWS = 25;
const int MAXCOLS = 25;

void setSize(int nr, int nc);
int getRows();
int getCols();
void setWall(int r, int c);
bool isWall(int r, int c);
void draw(int rStart, int cStart, int rEnd, int cEnd);
void draw(int rStart, int cStart, int rEnd, int cEnd, int rCar, int cCar);

#endif // GRID_INCLUDED
