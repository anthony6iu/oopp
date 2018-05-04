#include "game.hpp"
Game::
Game(){
	pair_values = new int[2];
	dice = new FakeDice;
	board = new Board;
	SB = new ScoreBoard;

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
	delete SB;
}

bool Game::
getNewPlayer() throw (BadPlayer, BadColor, BadName){
	int k = 0;
	for(k = 0; k < PLAYER; ++k){

		// declare some variables.
		string tempname; // save temporary player name.
		int tempcolor = 5; // save temporary player color.
		int a = 0;
		int b = 0;

		// player name input
		do{
			try{
				cout<<"Type player "<<(k+1)<<" name: (whitespace is not permitted.)\n";
				cin>>tempname;
				for(a = 0; a < PLAYER; ++a){
				// check temporary name if available.
					if(tempname == player_name_list[a]) throw BadName(tempname,5);
				}
			}
			catch(BadName& bn){bn.print();}
			catch(bad_alloc bn){cerr<<"Allocation error.\n";}
			catch(...){cerr<<"Last-ditch effort to catch exceptions.\n";};
		}while(a!=PLAYER);
		player_name_list[k] = tempname;

		// player color input.
		do{
			cout<<"Choose a color from:\n";
			for(int c = 1; c < 5; ++c){
				int d = 0;
				for(d = 0; d < PLAYER; ++d){
					if(c == player_color_list[d]) break;
				}
				if(d == PLAYER){
					cout<<c<<"."<<words[c]<<" ";
				}
			}
			cout<<"\n";
			// read color input 1st time.
			try{
				cin>>tempcolor;

				for(b = 0; b < PLAYER; ++b){
					// check temporary color if has been chosen.
					if(tempcolor == player_color_list[b]) throw BadColor(tempname,tempcolor);
					// check temporay color if invaild.(out of range)
					if(tempcolor < 1 || tempcolor > 4) throw BadColor(tempname,tempcolor);
				}
			}
			catch(BadColor& bc){bc.print();}
			catch(bad_alloc bn){cerr<<"Allocation error.\n";}
			catch(...){cerr<<"Last-ditch effort to catch exceptions.\n";};
		}while(b != PLAYER);
		player_color_list[k] = ColorEnum(tempcolor);

		// construct player()
		Player* pt = new Player(player_name_list[k],player_color_list[k]);
		player_list.insertBack(pt);
		delete pt;
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

// p12
void Game::
play(){
	Player* plyr = player_list.first();
	do{
		gstat = oneTurn(&plyr);
	}while(gstat==begun);
	if(gstat == done) {
		/*
		//p11
		string pname = (*plyr).Namegetter();
		int* pcol = (*plyr).SBgetter();
		// update to Scoreboard:
		char* c_pname = new char[pname.size()];
		copy(pname.begin(),pname.end(),c_pname);
		SB->update(c_pname,pcol);
		*/

		cout<<"\n\nCongratulation! Winner is:\n"<<*plyr<<"\nSee you next time.\n";
		// remove all players and update their infos to Scoreboard.
		do{
			// get current player info.
			string pname = (*plyr).Namegetter();
			int* opcol = (*plyr).SBgetter();
			// update info to Scoreboard:
			char* c_opname = new char[pname.size()];
			copy(pname.begin(),pname.end(),c_opname);
			SB->update(c_opname,opcol);
			// remove this player.
			plyr = player_list.remove();
		}while(player_list.count()!=0);
	}
	if(gstat == quit) cout<<"No more players. Game quit.\n";
};

GameStatus Game::
oneTurn(Player** p){
	board->startTurn(*p); // register player to board to start.
	cout<<"Current Player: "<<**p; // Print out current player's information.

	// Print out a menu:
	bool flag = false;
	do{
		cout<<"\n--------------------------------MENU----------------------------------\n";
		cout<<"1.Roll\n2.Stop\n3.Resign\n4.Show Scoreboard\n:";
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
					*p = player_list.next();
					flag = true;
				}
				cout<<*board; // Print board after finishing one dice move.
				break;
			}
			// Stop and finish this turn.
			case 2:{
				cout<<"############################# TURN STOP ##############################\n";
				board->stop(); 
				if((*p)->score() == 3) return done;
				else cout<<**p<<endl;
				*p = player_list.next();
				flag = true; 
				break;
			}
			// Remove this player from list.
			case 3:{
				cout<<"########################## PLAYER REMOVED ############################\n";
				
				//p11
				string pname = (*p)->Namegetter();
				int* pcol = (*p)->SBgetter();
				// update to Scoreboard:
				char* c_pname = new char[pname.size()];
				copy(pname.begin(),pname.end(),c_pname);
				SB->update(c_pname,pcol);

				*p = player_list.remove(); 
				if(*p == NULL) return quit;
				flag = true; 
				break; 
			}
			case 4:{
				cout<<*SB;
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






