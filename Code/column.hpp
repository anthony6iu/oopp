//
//  Column.hpp
//  Hongchi
//
//  Created by Hongchi Liu on 2/19/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef Column_hpp
#define Column_hpp

#include <fstream>
#include <iomanip> // format output
#include "tools.hpp"
#include "enums.hpp"
#include "Player.hpp"

class Column{
private:
    int ccnt = 0;
    static int colLength[13];
    int marker[5]={0,0,0,0,0};
    ColumnEnum column_state;
    int column_number;
    int column_length;
public:
    Column(int);
    ~Column();
    ColumnEnum state(){ return column_state; };
    ostream& print(ostream& out);
    //setter for test:
    void setter();
    // p5 column2 parts:
    bool startTower(Player*);
    bool move();
    void stop(Player*);
    void bust();
    // p5 assist.
    int getColNum(){return column_number;};
    // p6: modified Print() function.
    ostream& modified_print(ostream&, int);
};

inline ostream& operator << (ostream& out, Column& column){ return column.print(out); };
#endif /* Column_hpp */
