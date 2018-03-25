//
//  Player.cpp
//  P2-Hongchi
//
//  Created by Hongchi Liu on 2/8/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include "Player.hpp"

// constructor
Player::
Player(string name, ColorEnum color){
    PlayerName = name;
    PlayerColor = color;
    if(name == "") fatal("illegal player name.(name can not be empty)\n");
};

bool Player::
wonColumn(int colNum){
    if(Score < 3) ScoreBoard[Score++] = colNum;
    return (Score >= 3);
};

ostream& Player::
print(ostream& out){
    out<<"PlayerName: "<<setw(10)<<PlayerName<<"   PlayerColor: "<<setw(6)<<words[PlayerColor];
    if(PlayerColor != 5 && Score >0){
        out<<" Score: "<<Score;
        out<<" Won:";
        for(int j = 0; j<Score; ++j) out<<" "<<ScoreBoard[j];
    }
    else out<<endl;
    return out;
};
