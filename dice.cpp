//
//  dice.cpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 2/1/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include "dice.hpp"
Dice::
Dice(int n){
    // default constructor:
    nDice = n;
    pnDice = new int[nDice];
    //srand(time(NULL)); // I called srand() function at the beginning of unitDice() test function,
                         // so commented this line.
    roll(); // call roll() method to roll each dice.
};

Dice::
Dice(int n, int* pstatus){
    if(n > 0 && n < MAX_DICENUM + 1){
        nDice = n;
        pnDice = new int[nDice];
        roll();
        *pstatus = 1; // assgin status as true.
    }
    else {
        /*
            if input dicenums is bigger than accepted, just allocate 1 element array memory, then system can call
            ~Dice() correctly.
         */
        pnDice = new int[1];
        *pstatus = 0; // assign status as false.
    }
};

Dice::
~Dice(){
    delete [] pnDice; // free the dynamic memory that allocated.
};

const int* Dice::
roll(){
    for(int j = 0;j < nDice; ++j){
        pnDice[j] = rand() % 6 + 1;
    }
    return pnDice;
};
// this is the rules for "<<" to output a Dice class instance and add this rule to "<<" redefinition.
ostream& Dice::
print(ostream& out){
    for (int k = 0; k < nDice; ++k) {
        out<<pnDice[k];
        if(k < nDice - 1) out<<"-";
    }
    return out;
};

