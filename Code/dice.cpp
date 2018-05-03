//
//  dice.cpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 2/1/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include "dice.hpp"


Dice::
Dice(int n): nDice(n){
    pnDice = new int[nDice];
    //roll();
    cnt++;
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
    cnt++;
};

Dice::
~Dice(){
    delete [] pnDice; // free the dynamic memory that allocated.
    cout<<"$$$FREE MEMORY$$$ Dice count: "<<--cnt<<endl;
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
        if(k < nDice - 1) out<<" ";
    }
    out<<endl;
    return out;
};

const int* CantStopDice::
roll(){
    Dice::roll();
    for(int k = 0; k < DEFAULT_DICENUM ; ++k){
        cout<<char(97+k)<<": "<<pnDice[k]<<" ";
    }
    cout<<endl<<"Choose first pair(such as: ad or bc,then press ENTER.)"<<endl;
    char x,y;
    int count = 0;
    bool valid = false;
    do{
        if(count>4) fatal("Try too many times, exit.\n");
        cin.sync();cin.get(x);cin.get(y);cin.ignore(1);
        if(int(x) == int(y) || int(x) < 97 || int(x) > 100 || int(y) < 97 || int(y) > 100){
            cout<<"Choice is invalid. Try again.("<<++count<<")\n";
            continue;
        }
        valid = true;
    }while(valid == false);

    cin.clear();

    int one = pnDice[int(x)-97] + pnDice[int(y)-97];
    pnDice[int(x)-97] = pnDice[int(y)-97] = 0;
    int two = 0;
    for(int k = 0; k < DEFAULT_DICENUM; ++k){
        if(pnDice[k] != 0) two += pnDice[k];
    }
    PairSum[0] = one;
    PairSum[1] = two;
    cout<<PairSum[0]<<" "<<PairSum[1]<<endl;
    return PairSum;
};

FakeDice::
FakeDice(){
    input.open(FAKE_INPUT);
    if(!input.is_open()) fatal("Failed to open input file.\n");
};

const int* FakeDice::
roll(){
    cin.clear();
    int a,b,c,d;
    input>>a;input.ignore(1);input>>b;input.ignore(1);input>>c;input.ignore(1);input>>d;input.ignore(1);
    PairSum[0] = a+b; PairSum[1] = c+d;
    return PairSum;  
};


























