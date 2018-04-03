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

#define PLAYER 2
#define COLUMN_TEST_NUMBER 4
#define GAME_TEST_TIME 25
class Game{
private:
    string player_name_list[PLAYER];
    ColorEnum player_color_list[PLAYER];
    Dice* dice = new FakeDice;
    CList<Player> player_list;
    vector<Column> column_list;

    Board* board = new Board;
public:
    Game();
    ~Game();
    bool getNewPlayer();
    ostream& print(ostream&);
    // p5 test function.
    void p5test(ostream&);
    // p6 test function.
    void p6test(ostream&);
    // added by p8, to test dice in game.
    void p8test(ostream&);
};

inline ostream& operator << (ostream& out, Game& game){ return game.print(out); };
#endif /* Game_hpp */