#include "game.hpp"
Game::
Game(){
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






