//
//  Column.cpp
//  Hongchi
//
//  Created by Hongchi Liu on 2/19/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include "column.hpp"

// initial static member
int Column::colLength[13]={0,0,3,5,7,9,11,13,11,9,7,5,3};

// constructor
Column::
Column(int col_number){
    if(col_number < 13 && col_number > 1){
        column_number = col_number;
        column_state = ColumnEnum(2);
        column_length = colLength[column_number];
        ++ccnt;
    }
    else fatal("illegal input for Column constructor.");
}
Column::
~Column(){
    cout<<"$$$FREE MEMORY$$$ Column_"<<column_number<<" count: "<<--ccnt<<endl;
}
// print method
ostream& Column::
print(ostream& out){
    out<<"column: "<<setw(2)<<column_number<<" state: "<<setw(12)<<column_state_words[column_state]<<" ";
    for(int k = 1; k < colLength[column_number]+1; ++k){
        /*
        // empty slots
        if(k != column_length) out<<"-----|";
        // unempty slots
        else{
            for(int j = 0; j < 5; ++j){
                if(marker[j] == 1){
                    out<<CHAR[j];
                }
                else out<<"-";
            }
            out<<" ";
            //if call break next line, means that stop output at unempty slot.
            //break;
        }
        */
       for(int m = 0; m < 5; ++m){
            if(marker[m] == k){
                out<<CHAR[m];
                continue;
            }
            out<<"-";
       }
       out<<"|";
    }
    return out;
}

// setter() is only used for test purpose.
void Column::
setter(){
    /*
    // set slot
    for (int k = 0; k < 5; ++k) marker[k] = rand() % (column_length + 1);
    // set state
    int rand_state = rand() % 3;
    column_state = ColumnEnum(rand_state);
    */
    // commentted above to make p5 test easier.
    for (int k = 0; k < 5; ++k) marker[k] = 0;
    // set orange color player position below, to make p5 test easier.
    // start at random position 0,1,2.
    marker[1] = rand()%3;
    // start with random state 0,2.
    column_state = ColumnEnum(rand()%2 * 2);
}

//p5
// startTower()
bool Column::
startTower(Player* plyr){
    // check columen state:
    // column state is avaiable.
    if(column_state == ColumnEnum(2)){
        ColorEnum color = plyr->color();
        if(marker[(int)color] > 0){
            marker[0] = marker[(int)color];
            marker[(int)color] = 0;
        }
        return true;
        //return false;
    }
    // column state is captured.
    else return false;
}
// move()
bool Column::
move(){
    // if column is available now.
    if( column_state == ColumnEnum(2)){
        // tower moves 1 slot forward.
        ++marker[0];
        // if reach or over the top, after movement, set state to pending.
        if(!(column_length > marker[0])) column_state = ColumnEnum(1);
        return true;
    }
    return false;
}
// stop()
void Column::
stop(Player* plyr){
    ColorEnum color = plyr->color();
    marker[(int)color] = marker[0];
    marker[0] = 0;
    // if pending now, set to captured and plyr won this column.
    if( column_state == ColumnEnum(1)){
        if(plyr->wonColumn(column_number)) column_state = ColumnEnum(0);
    }
}
// bust()
void Column::
bust(){
    marker[0] = 0;
    column_state = ColumnEnum(2);
}

// p6
/*
    modified print() function.
    ostream& modified_print(ostream& out, int height);
    height is a new param to pass the current position on board display,
    the 1st line height is 13, the down to 1.
    line after height 1 is columne index.
    graph:
    13 |     |     |     |     |     |-----|     |     |     |     |     |
    12 |     |     |     |     |     |-----|     |     |     |     |     |
    11 |     |     |     |     |-----|-----|-----|     |     |     |     |
    ...
    ...
    ...
    01 |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
         C02 | C03 |...
 */
ostream& Column::
modified_print(ostream& out, int height){
    if(height > column_length) out<<"     "<<"|";
    else{
        for(int m = 0; m < 5; ++m){
            if(marker[m] == height){
                out<<CHAR[m];
                continue;
            }
            out<<"-";
        }
        out<<"|";
    }
    return out;
}










