//
//  main.cpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 1/30/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "tools.hpp"
#include "dice.hpp"

#define TEST_TIMES 10 // times to test.
#define TEST_nDice_RANGE 10 // for each test, the max value for nDice.

using namespace std;
void unitDice(ofstream& output);

int main(int argc, const char * argv[]) {
    
    ofstream myout; // output file name
    unitDice(myout); // call test plan
    return 0;
}

// test function
void unitDice(ofstream& output){
    output.open("output.txt",ios::app); // try to open output file.
    // open failed.
    if(!output.is_open()) fatal("failed to open output file.\n");
    // open successed.
    else{
        // set initialized status with 0, for testing undefault dice constructor.
        int stat = 0;
        int* pstatus = &stat;
        
        // initial banner() and random seed.
        banner(output);
        srand(time(NULL)); // I have to call the srand() function here,
                           // if I generate Dice instance more than one time.
                           // remember that: JUST call one time in this whole program, or the seed will be the same one.

        // output test information
        /*
         test with undefault constructor
         for each test, generate a random # of dice.
         */
        output<<"Test with un-default constructor:\n";
        output<<"generate "<<TEST_TIMES<<" times.\n";
        output<<"each time with different # of dice, random from 1-"<<TEST_nDice_RANGE<<".\n";
        output<<"the # of dice can be accepted is from 1-"<<MAX_DICENUM<<".\n";
        for(int n=0;n<TEST_TIMES;++n){
            output<<"Time "<<n+1<<": ";
            int tempnum = rand()%TEST_nDice_RANGE+1;
            Dice dice(tempnum,pstatus);
            if(!*pstatus){
                output<<tempnum<<" is an illegal dice num.\n";
                continue;
            }
            output<<dice;
            output<<"\n";// sperate output line for each test time
        }
        /*
            test with default constructor.
        */
        output<<"Test with default constructor:\n";
        Dice defaultdice;
        output<<defaultdice;
        // end test.
        output<<"\n-----------TEST END------------\n";
        bye();
        output.close(); // close stream.
    }
}
