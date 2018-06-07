#include "game.hpp"
Game::
Game(){
	pair_values = new int[2];
	gstat = begun;
	//dice = new FakeDice;
	dice = new CantStopDice;
	board = new Board;
	SB = new ScoreBoard;

	if(!getNewPlayer()) fatal("Failed to initialed.\n");
};

Game::
~Game(){
	delete dice;
	delete board;
	delete SB;
}

bool Game::
getNewPlayer() throw (BadPlayer, BadColor, BadName){
	bool ctn = true;
	int cnt = 0;
	int k = 0;

	while(ctn){
		cout<<"How many players in this game?(2-4)\n";
		cin>>cnt;
		if(1 < cnt && cnt < 5) ctn = false;
	}

	for(k = 0; k < cnt; ++k){
		// declare some variables.
		string tempname;   // save temporary player name.
		int tempcolor = 5; // save temporary player color.
		int a = 0;
		int b = 0;
		// player name input
		do{
			try{
				cout<<"Type player "<<(k+1)<<" name: (Whitespace is not permitted.)\n";
				cin>>tempname;
				for(a = 0; a < cnt; ++a){
				// check temporary name if available.
					if(tempname == player_name_list[a]) throw BadName(tempname,5);
				}
			}
			catch(BadName& bn){bn.print();}
			catch(bad_alloc bn){cerr<<"Allocation error.\n";}
			catch(...){cerr<<"Last-ditch effort to catch exceptions.\n";};
		}while(a!=cnt);
		player_name_list[k] = tempname;

		// player color input.
		do{
			cout<<"Choose a color from:\n";
			for(int c = 1; c < 5; ++c){
				int d = 0;
				for(d = 0; d < cnt; ++d){
					if(c == player_color_list[d]) break;
				}
				if(d == cnt){
					cout<<c<<"."<<words[c]<<" ";
				}
			}
			cout<<"\n";
			// read color input 1st time.
			try{
				cin>>tempcolor;

				for(b = 0; b < cnt; ++b){
					// check temporary color if has been chosen.
					if(tempcolor == player_color_list[b]) throw BadColor(tempname,tempcolor);
					// check temporay color if invaild.(out of range)
					if(tempcolor < 1 || tempcolor > 4) throw BadColor(tempname,tempcolor);
				}
			}
			catch(BadColor& bc){bc.print();}
			catch(bad_alloc bn){cerr<<"Allocation error.\n";}
			catch(...){cerr<<"Last-ditch effort to catch exceptions.\n";};
		}while(b != cnt);
		player_color_list[k] = ColorEnum(tempcolor);

		// construct player()
		Player* pt = new Player(player_name_list[k],player_color_list[k]);
		player_list.insertBack(pt);
	}

	cout<<"Input finished.\n";
	return true;
};

ostream& Game::
print(ostream& out){
	out<<player_list<<endl; // print players.
	out<<*board;            // print board.
	return out;
};

void Game::
play(){
	Player* plyr = player_list.first();
	do{
		gstat = oneTurn(&plyr);
	}while(gstat==begun);
	
	if(gstat == done) {
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
	//cout<<"Current Player: "<<**p; // Print out current player's information.

	// Print out a menu:
	bool flag = false;
	do{
		cout<<"\n";
		cout<<"\n----------------------------------------------------------------------\n";
		cout<<"Current: "<<**p;
		cout<<"\n>>------------------------------MENU--------------------------------<<\n";
		cout<<"1.Roll\n2.Stop\n3.Resign\n4.Show Scoreboard\n:";
		int choice  = 0;
		cin>>choice;
		switch(choice){
			// Normal roll and move step.
			case 1:{
				pair_values = dice->roll();
				//cout<<"Dice pairs sum are: "<<*dice; // print out the dice pairs.

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

				// remove tiles from board.
				ColorEnum pcolor = (*p)->Colorgetter();
				for(int j = 2; j < 13; ++j) board->getter(j)->setter(pcolor);

				// remove player from list.
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






