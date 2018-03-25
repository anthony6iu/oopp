//
//  Player.hpp
//  P2-Hongchi
//
//  Created by Hongchi Liu on 2/8/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//
#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <fstream>
#include <iomanip>
#include "enums.hpp"
#include "tools.hpp"

class Player{
private:
    string PlayerName;
    ColorEnum PlayerColor;
    int Score = 0;
    int ScoreBoard[3] = {0};
public:
    Player(string name = "default", ColorEnum color = ColorEnum(5));
    ostream& print(ostream& out);
    ColorEnum color(){ return PlayerColor; };
    int score(){ return Score; };
    bool wonColumn(int colNum);
    
};

inline ostream& operator << (ostream& out, Player& player){ return player.print(out); };
#endif /* Player_hpp */
