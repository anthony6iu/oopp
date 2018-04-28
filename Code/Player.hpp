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
    //p11
    int* SBgetter(){return ScoreBoard;};
    string Namegetter(){return PlayerName;};
};

inline ostream& operator << (ostream& out, Player& player){ return player.print(out); };



// p10 exception class: Badplayer();
class BadPlayer {
public:
	string Name;
	int Color;
	BadPlayer(string name, int color) : Name(name), Color(color) {};
	virtual void print(){
		cerr<<"Both name and color are wrong.\n";
		cerr<<"You entered "<<Name<<" and "<<words[Color]<<". Please reenter.\n";
	}

};

class BadName : public BadPlayer{
public:
	BadName(string name, int color) : BadPlayer(name,color){};
	virtual void print(){
		cerr<<"Illegal Name: "<<Name<<" has already existed. Please reenter.\n";
	}
};

class BadColor : public BadPlayer{
public:
	BadColor(string name, int color) : BadPlayer(name,color){};
	virtual void print(){
		cerr<<"Illegal Color. Please choose from list.\n";
	}
};


#endif /* Player_hpp */


