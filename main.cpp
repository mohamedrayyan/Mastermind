/* 
 * File:    main.cpp
 * Author:  Mohamed Rayyan
 * Created on September 13, 2019, 19:33
 */

//System Libraries
#include <cstdlib>
#include "Iris.h"

using namespace std;

//Function Prototypes
void aboutIris();
void check(Iris *&);

int main(int argc, char** argv) {
    aboutIris();
    
    //Declare variables && initialize Values
    bool found = false;
    Iris *iris = NULL;
    
    //Loop until solved and count to find solution
    int again = 1;
    
    do {
        iris = new Iris();

        check(iris);

        cout << iris->gtCode() << "\trr \trw \t#" << endl;

        for(int k = 0; k < 13; k++) {
            iris->AI();
            cout << iris->gtGuess() << "\t" << int(iris->gtRR()) << "\t" 
                    << int(iris->gtRW()) << "\t" << (k+1) << endl;

            if(iris->gtRR() == 4) {
                found = true;
                k = 13;
            }
            if(k == 13) {
                if(found) {
                    cout << "got it" << endl;
                }
                else {
                    cout << "gotn't" << endl;
                }
                cout <<"=========================================="<< endl;
            }
        }
        delete(iris);
        iris = NULL;
        found = false;
        
        cout << "Again? Yes = 1 No = anything\t";
        cin >> again;
        cin.clear();
        cin.ignore(1000,'\n');
    }while(again == 1);
    
    //Exit the program
    return 0;
}

void aboutIris() {
    cout << "IRIS version 19";
    cout << "\tCreated by Mohamed Rayyan" << endl;
    cout << "Enter a 4 digit code to crack." << endl << endl;
}

void check(Iris *&iris) {
    bool valid = false;
    while(!valid || iris->gtCode().length() != 4) {
        cout << "Enter code to crack: ";
        getline(cin,iris->stCode());
        for(int i = 0; i < 4; i++) {
            if(iris->gtCode()[i] >= 48 && iris->gtCode()[i] <=57) {
                valid = true;
            }
            else {
                valid = false;
                break;
            }
        }
    }
}