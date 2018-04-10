#include "game.hpp"
Game::
Game(){
	pair_values = new int[2];
	dice = new FakeDice;
	board = new Board;

	gstat = begun;

	// construct players.
	if(!getNewPlayer()) fatal("Failed to initialed.\n");
	/*
	// construct columns.
	for(int k = 0; k < COLUMN_TEST_NUMBER; ++k){
		Column temp(rand() % (12 -1) + 2);
		temp.setter();
		column_list.push_back(temp);
	}
	*/
	
	// construct dice.
	//dice = new FakeDice;
	// construct board.
	//board = new Board;
};
Game::
~Game(){
	delete dice;
	delete board;
}

bool Game::
getNewPlayer(){
	int k = 0;
	for(k = 0; k < PLAYER; ++k){

		// declare some variables.
		string tempname; // save temporary player name.
		int tempcolor; // save temporary player color.
		int a = 0;
		int b = 0;

		// player name input
		cout<<"Type player "<<(k+1)<<" name:\n";
		cin>>tempname;
		do{
			for(a = 0; a < PLAYER; ++a){
				// check temporary name if available.
				if(tempname == player_name_list[a]){
					cout<<"This name already existed. Enter another one.\n";
					//reread name input.
					cin>>tempname;
					break;
				}
			}
		}while(a != PLAYER);
		player_name_list[k] = tempname;

		// player color input.
		cout<<"Choose a color from:\n";
		for(int c = 1; c < 5; ++c){
			int d = 0;
			for(d = 0; d < PLAYER; ++d){
				if(ColorEnum(c) == player_color_list[d]) break;
			}
			if(d == PLAYER){
				cout<<c<<"."<<words[c]<<" ";
			}
		}
		cout<<"\n";
		// read color input 1st time.
		cin>>tempcolor;
		do{
			for(b = 0; b < PLAYER; ++b){
				// check temporary color if has been chosen.
				if(ColorEnum(tempcolor) == player_color_list[b]){
					cout<<"This color already existed. Enter another one:\n";
					// reread new input.
					cin>>tempcolor;
					break;
				}
				// check temporay color if invaild.(out of range)
				if(tempcolor < 1 || tempcolor > 4){
					cout<<"This color is out of range. Enter another one:\n";
					// reread new input.
					cin>>tempcolor;
					break;
				}
			}
		}while(b != PLAYER);

		player_color_list[k] = ColorEnum(tempcolor);
		// construct player()
		Player* pt = new Player(player_name_list[k],player_color_list[k]);
		player_list.insertBack(pt);
		//delete pt;
	}
	// end words.
	cout<<"Input finished.\n";
	return (k == PLAYER);
};

ostream& Game::
print(ostream& out){
	/*
	// print dice.
	out<<"Dices # are: "<<(*dice)<<endl;
	*/

	out<<player_list<<endl; // print players.

	/*
	// print columns.
	for(vector<Column>::iterator iter = column_list.begin(); iter != column_list.end(); ++iter){
		out<<*iter<<endl;
	}
	*/

	// print board.
	out<<*board;
	return out;
};

// p9

void Game::
play(){
	Player plyr = *(player_list.first());
	for(int i = 0; i < TURN_TEST_TIME; ++i){
		oneTurn(&plyr);
	}
};

GameStatus Game::
oneTurn(Player* p){
	board->startTurn(p); // register player to board to start.
	cout<<"Current Player: "<<*p; // Print out current player's information.

	// Print out a menu:
	bool flag = false;
	do{
		cout<<"\n--------------------------------MENU----------------------------------\n";
		cout<<"1.Roll\n2.Stop\n3.Resign\n:";
		int choice  = 0;
		cin>>choice;
		switch(choice){
			// Normal roll and move step.
			case 1:{
				pair_values = dice->roll();
				cout<<"Dice pairs sum are: "<<*dice; // print out the dice pairs.

				bool step1 = board->move(pair_values[0]); //  First pair sum move.
				bool step2 = board->move(pair_values[1]); // Second pair sum move.
				// If both pairs sum can not be chosen, bust and finish this turn.
				if(!step1 and !step2){
					cout<<"############################# TURN BUST ##############################\n";
					board->bust();
					*p = *(player_list.next());
					flag = true;
				}
				cout<<*board; // Print board after finishing one dice move.
				break;
			}
			// Stop and finish this turn.
			case 2:{
				cout<<"############################# TURN STOP ##############################\n";
				board->stop(); 
				*p = *(player_list.next());
				flag = true; 
				break;
			}
			// Remove this player from list.
			case 3:{
				cout<<"########################## PLAYER REMOVED ############################\n";
				*p = *(player_list.remove()); 
				flag = true; 
				break; 
			}
			// When input selection choice is invalid. Let user reinput.
			default: {
				cout<<"Invalid selection. Try again.\n";
				break;
			}
		};
	}while(!flag);
	cout<<"Turn finished. Board now is like:\n"<<*board;

	return begun;
};




void Game::
p5test(ostream& out){
	for(int k = 0; k < COLUMN_TEST_NUMBER; ++k){
		int movetime = 0;
		// if start tower successful.(not be captured.)
		if(column_list[k].startTower(player_list.first())){
			while(column_list[k].move()){
				out<<"Column "<<column_list[k].getColNum()<<": move one slot.\n";
				// at most move 4 slots.
				if (++movetime == 4) break; 
			}
			// just test bust() method, no logical meaning.
			if(k == 2){
				out<<"The 3rd column will call bust() as test goal.\n";
				column_list[k].bust();
			}
			out<<"\nBefore call stop():\n"<<column_list[k]<<endl<<endl;
			// do stop() action.
			column_list[k].stop(player_list.first());
			// 
			out<<"Player move test on column "<<column_list[k].getColNum()<<" is finished.\n";

		}
		// if start tower failed.(be captured.)
		else{
			out<<"Tower can not be placed at column "<<column_list[k].getColNum()<<", which is captured.\n";
		}
	}

	//column_list[0].bust();
}


void Game::
p6test(ostream& out){
	// use player[0] whose color is orange (1) to test p6.
    board->startTurn(player_list.first()); // start player[0] turn.
    int times = GAME_TEST_TIME; // test time.
    out<<"Do test range from column 6 - 8. Make "<<times<<" times move()."<<endl;
    for(int i=0;i<times;++i){
    	int choice = rand()%3+6; // choose move column randomly.
        if(!(board->move(choice))){
        	out<<"No more tower on columen "<<choice<<", do bust()."<<endl;     	
        	board->bust();
        	break;
        }
        out<<"Move one slot on column "<<choice<<"."<<endl;
    }
    out<<"Player turn finised."<<endl;
    board->stop();
}

void Game::
p8test(ostream& out){
	
	for(int k = 0; k < 20; ++k){
		Player* now;
		if(k==0) now = player_list.first();
		else     now = player_list.next();

		board->startTurn(now);           // register current player to board.

		const int* pPair = dice->roll(); // roll dice and generate 2 pairs -- pPair[0] and pPair[1].

		out<<"Current Player: "<<*now<<"Choice: "<<pPair[0]<<" and "<<pPair[1]<<endl;

		if(!board->move(pPair[0])){
			board->stop();
			out<<*board;
			continue;
		}
		if(!board->move(pPair[1])){
			board->stop();
			out<<*board;
			continue;
		}
		board->stop();
		out<<*board;
	}
}






