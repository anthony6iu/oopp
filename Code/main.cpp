//
//  main.cpp
//  P1-Hongchi
//
//  Created by Hongchi Liu on 1/30/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#include <fstream>
#include "tools.hpp"
#include "game.hpp"

void unitGame();

// main()
int main(int argc, const char * argv[]) {
    srand(time(NULL));
    unitGame(); // p12
    return 0;
}

void unitGame(){
    Game game;
    cout<<"\n--------------------------Turn test starts.---------------------------\n";
    game.play();
    cout<<"-------------------------Turn test finished.--------------------------\n";
    cout<<"------------------------Copyright  ©  Hongchi-------------------------\n";

}




























