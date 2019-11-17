//
//  main.cpp
//  HelloThree
//
//  Created by Srishti Dhawan on 5/1/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "grid.h"
using namespace std;


// function returns true if its parameter is a syntactically valid course, and false otherwise
bool isCourseWellFormed(string course) {
    double total_len = course.length();
    //confirms the string begins with a direction
    if (!(isalpha(course[0]))) {
        return false;
    }
    double test = 0;
    
    while (test < total_len) {
        if(course[test] == 'N' || course[test] == 'n' || course[test] == 'E' || course[test] == 'e' || course[test] == 'S' || course[test] == 's' || course[test] == 'W' || course[test]== 'w') {
            test++;
            if (isdigit(course[test])) {
                test++;
                if (isdigit(course[test])) {
                    test++;
                    if (isdigit(course[test])) {
                        return false;
                    }
                }
            }
        }
        else {
            return false;
        }
    }
    return true;
}


//function determines the number of steps a car starting at position (r,c) could travel in the direction indicated by dir
int driveSegment(int r, int c, char dir, int maxSteps) {
    if (r<0 || r > getRows() || c<0 || c > getCols() ){
        return -1;
    }
    if (r>0 && r<= getRows() && c>0 && c<=getCols() && (isWall(r,c))){
        return -1;
    }
    if (maxSteps < 0) {
        return -1;
    }
    // checks the number of steps the car can go depending on the direction given
    int steps = 0;
    if (dir == 'N' || dir == 'n' ) {
        int i;
        for (i=r; i > 0; i--) {
            if ((i-1)== 0) {
                break;
            }
            if ((i-1)>0 && isWall((i-1), c)) {
                break;
            }
            steps++;
        }
    }
    if (dir == 'E' || dir == 'e' ) {
        int i;
        for (i=c; i< getCols(); i++) {
            if ((i+1) >> getCols()) {
                break;
            }
            if ((i+1)<= getCols () && isWall(r,(i+1))) {
                break;
            }
            steps++;
        }
    }
    if (dir == 'S' || dir == 's' ) {
        int i;
        for (i=r; i< getRows(); i++) {
            if ((i+1) >> getRows()) {
                break;
            }
            if ((i+1)<= getRows () && isWall((i+1),c)) {
                break;
            }
            steps++;
        }
    }
    if (dir == 'W' || dir == 'w' ) {
        int i;
        for (i=c; i > 0; i--) {
            if ((i-1)== 0) {
                break;
            }
            if ((i-1)>0 && isWall(r, (i-1))) {
                break;
            }
            steps++;
        }
    }
    if (maxSteps <= steps) {
        return maxSteps;
    }
    else {
        return steps;
    }
}


// determines the number of steps a car starting at position (sr,sc) travels when following the indicated course, which should lead to the end position (er,ec)
int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps) {
    if (sr<=0 || sr > getRows() || sc<=0 || sc > getCols() ){
        return 2;
    }
    if (er<=0 || er > getRows() || ec<=0 || ec > getCols() ){
        return 2;
    }
    if (sr>0 && sr<= getRows() && sc>0 && sc<=getCols() && (isWall(sr,sc))){
        return 2;
    }
    if (er>0 && er<= getRows() && ec>0 && ec<=getCols() && (isWall(er,ec))){
        return 2;
    }
    if (!isCourseWellFormed(course)) {
        return 2;
    }
    
  
    int test=0;
    double total_len = course.length();
    double steps=0;
    double total_steps=0;
    int my_er = sr;
    int my_ec = sc;
    char direction;
    
    while (test < total_len) {
        direction = course[test];
        test++;
        if (test < total_len) {
            if (isdigit(course[test])) {
                steps= course[test] - 48;
                test++;
                if (test < total_len) {
                    if (isdigit(course[test])) {
                        steps = (steps*10) + (course[test]-48);
                        test++;
                    }
                }
            }
            else {
                steps=1;
            }
        }
        
        
        int move = driveSegment(my_er, my_ec, direction, steps);
        
        total_steps = total_steps + move;
        
        if (direction == 'N' || direction == 'n' ){
            my_er = my_er - move;
        }
        if (direction == 'E' || direction == 'e' ){
            my_ec = my_ec + move;
        }
        if (direction == 'S' || direction == 's' ){
            my_er = my_er + move;
        }
        if (direction == 'W' || direction == 'w' ){
            my_ec = my_ec - move;
        }
        
        if (move!=steps) {
            nsteps = total_steps;
            return 3;
        }
        
    }
    
    
    
    nsteps= total_steps;
    
    if (my_er == er && my_ec == ec){
        return 0;
    }
    else {
        return 1;
    }
}


int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    assert(isCourseWellFormed("N2eE01n0s2e1"));
    assert(!isCourseWellFormed("e1x"));
    assert(driveSegment(3, 1, 'N', 2) == 2);
    int len;
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(3,1, 3,4, "N2eE01n0s2e1", len) == 0  &&  len == 7);
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(3,1, 3,4, "e1x", len) == 2  &&  len == -999);
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(2,4, 1,1, "w3n1", len) == 3  &&  len == 1);
    cout << "All tests succeeded" << endl;
}
