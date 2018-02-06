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

#define DEFAULT_DICENUM 4 // default dice # for constructor.
#define MAX_DICENUM 6  // max dice # can be accepted.

using namespace std;

class Dice{
private:
    int nDice;
    int* pnDice;
public:
    Dice(int n=DEFAULT_DICENUM); // default with DEFAULT_DICNUM.
    Dice(int, int*); // undefault constructor
    ~Dice();
    ostream& print(ostream&);
    const int* roll();
};

/*
    2 params for operator is out and dice, the purpose should be like: out<<dice;
    and you should tell compiler how the "<<" work when right side is a class.
    the rule is defined within print() member method.
 */
inline ostream& operator << (ostream& out, Dice& dice){return dice.print(out);};
#endif /* dice_hpp */
