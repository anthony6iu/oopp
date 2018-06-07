//
//  dice.hpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 2/1/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef dice_hpp
#define dice_hpp

#include <stdio.h>
#include <random>
#include <iostream>
#include <fstream>
#include "tools.hpp"
#include <iomanip> // format output

#define DEFAULT_DICENUM 4 // default dice # for constructor.
#define MAX_DICENUM 6  // max dice # can be accepted.
#define FAKE_INPUT "./fake_input.txt" // input file for FakeDice.

using namespace std;

class Dice{
private:
    int cnt = 0;
public:
    Dice(int n = DEFAULT_DICENUM); // default with DEFAULT_DICNUM.
    Dice(int, int*); // undefault constructor.
    ~Dice();
    virtual ostream& print(ostream&);
    virtual const int* roll();
protected:
    int nDice;
    int* pnDice;
};

class CantStopDice:public Dice{
public:
    int PairSum[2];
    CantStopDice():Dice(4){};
    ~CantStopDice(){};
    virtual const int* roll();
};

class FakeDice:public CantStopDice{
private:
    ifstream input;
public:
    FakeDice();
    ~FakeDice(){input.close();};
    const int* roll();
    ostream& print(ostream& out){return out<<setw(2)<<PairSum[0]<<" "<<setw(2)<<PairSum[1]<<endl;};
};
/*
    2 params for operator is out and dice, the purpose should be like: out<<dice;
    and you should tell compiler how the "<<" work when right side is a class.
    the rule is defined within print() member method.
 */
inline ostream& operator << (ostream& out, Dice& dice){ return dice.print(out); };
//inline ostream& operator << (ostream& out, FakeDice& dice){ return dice.print(out); };



#endif /* dice_hpp */
