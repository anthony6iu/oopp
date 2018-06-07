//
//  Game.hpp
//  P4-Hongchi
//
//  Created by Hongchi Liu on 2/24/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <fstream>
#include <iomanip> // format output
#include <string>
#include <vector>

#include "tools.hpp"
#include "enums.hpp"
#include "dice.hpp"
#include "Player.hpp"
#include "column.hpp"
#include "board.hpp"
#include "CList.hpp"
#include "ScoreBoard.hpp"

#define PLAYER 4

class Game{
private:
    // temp store players' infos.
    string player_name_list[PLAYER];
    ColorEnum player_color_list[PLAYER];

    Dice* dice;
    
    CList<Player> player_list;
    
    vector<Column> column_list;

    Board* board;
    // current pair-values of the dice.
    const int* pair_values;
    GameStatus gstat;              // the game status.
    GameStatus oneTurn(Player**); // a private function called by play().

    ScoreBoard* SB;

public:
    Game();
    ~Game();
    bool getNewPlayer() throw (BadPlayer, BadName, BadColor);
    // p9 
    void play();
    ostream& print(ostream&);
};

inline ostream& operator << (ostream& out, Game& game){ return game.print(out); };
#endif /* Game_hpp */