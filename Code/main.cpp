//
//  main.cpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 1/30/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include <fstream>
#include "tools.hpp"
//p1
#include "dice.hpp"
//p2
#include "Player.hpp"
//p3,p5
#include "column.hpp"
//p4
#include "game.hpp"
//p6
#include "board.hpp"
//p7
#include "CList.hpp"
//#include "CList.cpp"
//p1
#define DICE_TEST_TIMES 10 // times to test.
#define TEST_nDice_RANGE 10 // for each test, the max value for nDice.
//p2
#define PLAYER_TEST_TIME 10 // player class test times
//p3
#define COLUMN_TEST_TIME 11 // column class test times column 2-12

//6
#define BOARD_TEST_TIME 5
//P1
void unitDice(ofstream& out);
//p2
void unitPlayer(ofstream& out);
//P3
void unitColumn(ofstream& out);
//p4
void unitGame(ofstream&);
//p5
void unitColumn2(ofstream&);
//p6
void unitBoard(ofstream&);
//p7
void unitCList(ofstream&);
//p8
void unitCSD(ofstream&);
void unitFake(ofstream&);
//p9
void unitTurn();

// main()
int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    ofstream myout; // output file name
    
    //unitDice(myout);   // p1 test plan
    //unitPlayer(myout); // p2 test plan
    //unitColumn(myout); // p3 test plan
    //unitGame(myout); // p4 test plan
    //unitColumn2(myout);
    //unitBoard(myout);
    //unitCList(myout);
    
    // p8 test plan.
    //unitCSD(myout);
    //unitFake(myout);

    unitTurn(); // p9
    return 0;
}

// p1 test function
void unitDice(ofstream& output){
    output.open("output.txt"); // try to open output file.
    // open failed.
    if(!output.is_open()) fatal("failed to open output file.\n");
    // open successed.
    else{
        // set initialized status with 0, for testing undefault dice constructor.
        int stat = 0;
        int* pstatus = &stat;
        
        // initial banner() and random seed.
        banner(output);
        srand(time(NULL)); // I have to call the srand() function here,
                           // if I generate Dice instance more than one time.
                           // remember that: JUST call one time in this whole program, or the seed will be the same one.

        // output test information
        /*
         test with undefault constructor
         for each test, generate a random # of dice.
         */
        output<<"Test with un-default constructor:\n";
        output<<"generate "<<DICE_TEST_TIMES<<" times.\n";
        output<<"each time with different # of dice, random from 1-"<<TEST_nDice_RANGE<<".\n";
        output<<"the # of dice can be accepted is from 1-"<<MAX_DICENUM<<".\n";
        for(int n = 0;n < DICE_TEST_TIMES; ++n){
            output<<"Time "<<n + 1<<": ";
            int tempnum = rand() % TEST_nDice_RANGE + 1;
            Dice dice(tempnum,pstatus);
            if(!*pstatus){
                output<<tempnum<<" is an illegal dice num.\n";
                continue;
            }
            output<<dice;
            output<<"\n";// sperate output line for each test time
        }
        /*
            test with default constructor.
        */
        output<<"Test with default constructor:\n";
        Dice defaultdice;
        output<<defaultdice<<"\n";
        // end test.
        output<<"--------Dice() TEST END------------\n";
        output.close(); // close stream.
    }
}

//p2 test function
void unitPlayer(ofstream& out){
    out.open("output.txt",ios::app);
    // open output file failed.
    if(!out.is_open()) fatal("output file open failed.\n");
    // open successful.
    out<<"Test Player class:\n";
    // general test:
    out<<"Test "<<PLAYER_TEST_TIME<<" times with different color:\n";
    for(int k = 0;k < PLAYER_TEST_TIME; ++k){
        // generate different player names.
        char st[10];
        sprintf(st, "demo_%d",k);
        string testname = (string)st;
        
        // generate different colors.
        ColorEnum testcolor;
        char flag = 'F';
        if(k > -1 && k < 5) flag = 'T';
        switch (flag) {
            case 'T':
                testcolor = ColorEnum(k);
                break;
            default:
                testcolor = ColorEnum(5);
                break;
        }
        
        // create player instances and print out.
        Player temp(testname,testcolor);
        for(int r = 0; r < rand() % 3 + 1; ++r){
            temp.wonColumn(rand() % (12 - 1) + 2);
        }
        out<<temp<<"\n";
    }
    out<<"--------Player() TEST END------------\n";
    out.close();
    /*
    // unexpected test:
    string nullname="";
    Player nullnamedemo(nullname,ColorEnum(1));
     */
};

//p3 test function
void unitColumn(ofstream& out){
    out.open("output.txt",ios::app);
    // open output file failed.
    if(!out.is_open()) fatal("output file open failed.\n");
    // open successful
    out<<"Test Column class:\n";
    // normal test:
    for(int k = 2; k < COLUMN_TEST_TIME + 2; ++k){
        Column temp(k);
        temp.setter();
        out<<temp;
    }
    out<<"--------Column() TEST END------------\n";
    out.close();
    /*
    // unexpected test:
    Column illegaldemo(14);
    */
};

// p4 test function.
void unitGame(ofstream& out){
    out.open("Game_test_output.txt");
    // open failed.
    if(!out.is_open()) fatal("output file open failed.\n");
    // open succeed.
    banner(out);
    Game test;
    out<<test;
    out<<"-----------Game() TEST END------------\n";
    out.close();
};

// p5 test function.
void unitColumn2(ofstream& out){
    out.open("output.txt",ios::app);
    // open failed.
    if(!out.is_open()) fatal("output file open failed.\n");
    // opne succeed.
    banner(out);
    Game demo;
    out<<"\n----Before Column test have been called.-----\n";
    out<<demo;
    out<<"\n--------------Processing test.---------------\n";
    /*
    call a Game method--p5test() for testing.
    it is easy to see the difference before and after movement.
    also do some modification on Column::setter() to make p5 test plan easier.
     */
    demo.p5test(out);
    out<<"\n-----After Column test have been called.-----\n";
    out<<demo;
    out<<"-------------Column2 test finished-------------\n";
    out.close();
}

// p6 test function.
void unitBoard(ofstream& out){
    out.open("output.txt",ios::app);
    // open failed.
    if(!out.is_open()) fatal("output file open failed.\n");
    // opne succeed.
    banner(out);
    Game demo;

    // before test.
    out<<"@@--Before movement.--@@"<<endl;
    out<<demo;
    demo.p6test(out);
    // after test.        
    out<<"@@--After movement.--@@"<<endl;
    out<<demo;
    out<<"-------------Board test finished.--------------\n";

    out.close();
}

//p7 test function.
void unitCList(ofstream& out){
    out.open("CList_test_output.txt");
    banner(out);    
    CList<Player> clist;
    string name[4] = {"hunter","mage","priest","warrior"};
    out<<"Try to add: ";
    for(int a =0; a < 4; ++a){
        out<<name[a]<<"("<<words[a]<<") ";
    }
    out<<" to CList."<<endl;
    // create players and add to CList.
    for(int a = 0; a < 4; ++a){
        Player* temp = new Player(name[a],ColorEnum(a+1));
        out<<"Add "<<name[a]<<" to CList."<<endl;
        clist.insertBack(temp);
    }
    out<<"-----All players have been saved.-----"<<endl;
    out<<"-------Print whole list first:--------"<<endl;
    out<<clist;
    out<<"--------Call next() in a loop.--------"<<endl;
    for(int a = 0; a < 8; ++a){
        out<<*(clist.next());
    }
    out<<"---------Remove first player:---------"<<endl;
    clist.remove();
    out<<"-------------Print list:--------------"<<endl;
    out<<clist;
    out<<"---------Remove second player:--------"<<endl;
    clist.next();
    clist.remove();
    out<<"-------------Print list:--------------"<<endl;
    out<<clist;
    out<<"-----------Add a new player.----------"<<endl;
    Player* np1 = new Player("new1",ColorEnum(1));
    clist.insertBack(np1);
    out<<"-------------Print list:--------------"<<endl;
    out<<clist;
    out<<"-----------Remove all left.-----------"<<endl;
    clist.remove();clist.remove();clist.remove();
    out<<"-----------Print list now.------------"<<endl;
    out<<clist;
    out<<"----------Add 2 new players.----------"<<endl;
    Player* np2 = new Player("new2",ColorEnum(2));
    clist.insertBack(np2);
    Player* np3 = new Player("new3",ColorEnum(3));
    clist.insertBack(np3); 
    out<<"-----------Print list now.------------"<<endl;
    out<<clist;
    out.close();
    //
    delete np1;
    delete np2;
    delete np3;
}

// p8 CantStopDice test
void unitCSD(ofstream& out){
    Dice* CSDtest = new CantStopDice();
    CSDtest->roll();

    /*
    // generate fake_input.txt
    ofstream myout;
    myout.open(FAKE_INPUT);
    for(int k = 0; k < 100; ++k){
        Dice temp(4);
        temp.roll();
        myout<<temp;
    }
    myout.close();
    */
}


void unitFake(ofstream& out){
    out.open("fake_output.txt");
    // open failed.
    if(!out.is_open()) fatal("Output file open failed.\n");
    // opne succeed.
    banner(out);

    // test FakeDice in game.
    Game game;
    game.p8test(out);
}

void unitTurn(){

    Game game;
    cout<<"Construct successful.\n";
    game.play();
}




























