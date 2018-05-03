//
//  Game.hpp
//  P4-Hongchi
//
//  Created by Hongchi Liu on 2/24/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <fstream>
#include <iomanip> // format output
#include <string>
#include <vector>

#include "tools.hpp"
#include "column.hpp"
#include "Player.hpp"

class Board{
private:
    int cnt = 0;
    static int ColLen[13];
    
    int towerCounter; // a counter to say how many towers are in use.
    int towerLocation[3]; // an arrray of length 3 that tells which columns contain those towers.
    Column* backBone[13]; // contain 13 column pointers.
    Player* currPlayer; // current player.
    // own need functions.
public:
    Board();
    ~Board();// destructor.
    ostream& print(ostream&);
    void startTurn(Player*);
    bool move(int column);
    void stop();
    void bust();
};

inline ostream& operator << (ostream& out, Board& board){ return board.print(out); };

#endif /* Board_hpp */