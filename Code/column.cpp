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

bool Column::
startTower(Player* plyr){
    // check columen state:
    // column state is avaiable.
    if(column_state == ColumnEnum(2)){
        ColorEnum color = plyr->color();
        if(marker[(int)color] > 0){
            marker[0] = marker[(int)color];
            //marker[(int)color] = 0;
        }
        return true;
        //return false;
    }
    // column state is captured.
    else return false;
}

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

void Column::
bust(){
    marker[0] = 0;
    column_state = ColumnEnum(2);
}

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










