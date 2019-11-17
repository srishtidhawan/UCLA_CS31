//
//  main.cpp
//  Project_Two
//
//  Created by Srishti Dhawan on 4/18/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//



#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    
    double initial_read;
    double final_read;
    string name = "";
    int month;
    cout << fixed;
    cout << setprecision(2);
    
    cout << "Initial meter reading: " ;
    cin >> initial_read;
    cout << "Final meter reading: ";
    cin >> final_read;
    cin.ignore(10000, '\n');
    cout << "Customer name: ";
    getline(cin, name);
 //   cin.ignore(10000, '\n');
    cout << "Month number: ";
    cin >> month;
    cout << "---" << endl;
    /*
     The following code confirms that all the values given follow the rules:
        Initial reading is positive
        The final reading is greater than the initial
        An actual name and month are given
     */
    if ( initial_read < 0) {
        cout << "The initial meter reading must be nonnegative." <<endl;
        return 0;
    }
    if (final_read < initial_read){
        cout << "The final meter reading must be at least as large as the initial reading." << endl;
        return 0;
    }
    if ( name == "")  {
        cout << "You must enter a customer name." <<endl;
        return 0;
    }
    if ( month < 1 || month > 12) {
        cout << "The month number must be in the range 1 through 12." << endl;
        return 0;
    }
    //If the month is high, this code will figure out the total price.
    else {
        if (month >= 4 && month <= 10) {
            double delta = final_read - initial_read;
            double price;
            if (delta > 43) {
                price = (43 * 2.71) + ((delta-43) * 3.39);
            }
            else {
                price = delta * 2.71;
            }
            cout << "The bill for " << name << " is $" << price;
        }
    //If the month is low, this code will figure out the total price.
        else {
            double delta = final_read - initial_read;
            double price;
            if ( delta > 29) {
                price = ( 29 * 2.71) + ((delta-29) * 2.87);
            }
            else {
                price = delta*2.71;
            }
            cout << "The bill for " << name << " is $" << price;
        }
    }
    cout << endl;
    return 0;
}
