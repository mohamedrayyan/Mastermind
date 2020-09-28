/* 
 * File:    Iris.h
 * Author:  Mohamed Rayyan
 * Created on September 13, 2019, 19:33
 */

#ifndef IRIS_H
#define	IRIS_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include "Data.h"
#include "Detail.h"

using namespace std;

class Iris {
private:
    int skipped  = 0;           // Number of skipped guess because sum == 0   
    int counter  = -1;          // Number of guess
    int fllw     = 0;           // Index to previous guess        
    int lead     = 1;           // Current guess
    int indx     = 0;           // Index    
    int logir    = 0;           // Log[i].rr
    int logiw    = 0;           // Log[i].rw
    int pssibls  = 0;           // pssibl[indx].s
    int pssiblh  = 0;           // pssibl[indx].h
    vector<Data> log;           // Log of previous tries
    vector<Detail> pssibl;      // Possible digits
    set<char> ntPssibl;         // Not possible digits
    string code  = "0";         // Code
    string guess = "0";         // Guess
    string range = "0123456789";// Range 
    char dummy   = '\n';        // Dummy place holder
    char rr      = 0;           // Right in right spot AKA s for star
    char rw      = 0;           // Right in wrong spot AKA h for hash
    bool swapped = true;        // If swapping digits in code occured
    bool first   = true;        // First guess
    
    void fil(Data &temp);       // Fill code with digits during learning
    void swap(Data &temp, Data log, int n); // Swap code Digits
    bool inNtPssibl(Data log);  // Search for digit in ntPssibl
    bool inPssibl(Data log);    // Search for digit in pssibl
    void addToNtPssibll();      // Add digit to ntPssibl
    void yosheveti(Data &temp); // Fill code with digits after learning
    void eval();
public:
    Iris();
    ~Iris();
    void AI();                  // AI to crack the code
    string &stCode();           // Set the code
    string gtCode();            // Get the code
    string gtGuess();           // Get guess
    char gtRR();                // Get right in right spot
    char gtRW();                // Get right in wrong spot
};
#endif	/* IRIS_H */