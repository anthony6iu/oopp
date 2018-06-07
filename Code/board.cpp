#include "board.hpp"

// initial static column length array.
int Board::
ColLen[13]={0,0,3,5,7,9,11,13,11,9,7,5,3};

Board::
Board(){
	for(int k = 0; k < 13; ++k){
		// initial 0 and 1 to NULL.
		if(k < 2){
			backBone[k] = NULL;
			continue;
		}
		// initial 2 to 12 with Column pointer.
		backBone[k] = new Column(k);
	}
	cnt++;
};

Board::
~Board(){
	// free the memory allocated to backBone[2-12].
	for(int k = 2; k < 13 ; ++k) delete backBone[k];
	cout<<"$$$FREE MEMORY$$$ Board count: "<<--cnt<<endl;
};

ostream& Board::
print(ostream& out){
	// print column state.
	out<<"ST |";
	string state;
	for(int c = 2; c <13; ++c){
		if(backBone[c]->state() == ColumnEnum(0)) state = "CAP";
		if(backBone[c]->state() == ColumnEnum(1)) state = "PEN";
		if(backBone[c]->state() == ColumnEnum(2)) state = "AVA";
		out<<" "<<state<<" |";
	}
	out<<endl;

	// print column information.
	for(int h = 13; h > 0; --h){
		out<<setw(2)<<h<<" |";
		for(int c = 2; c < 13 ; ++c){
			backBone[c]->modified_print(out,h);
		}
		out<<endl;
	}

	// print column index.
	out<<"   |";
	for(int x = 2; x < 13; ++x){
		out<<" C"<<setw(2)<<x<<" |";
	}
	out<<endl;

	return out;
};

void Board::
startTurn(Player* plyr){
	currPlayer = plyr;
	towerCounter = 0;
	for(int k = 0; k < 3; ++k) towerLocation[k] =0;
};

bool Board::
move(int column){
	if(backBone[column]->state() == ColumnEnum(0)) return false; // captured.
	int t = 0;
	for(t = 0; t < 3; ++t){
		if(towerLocation[t] == column) break;
	}
	if(towerCounter == 3 && t == 3) return false; // no more tower available.
	if(backBone[column]->startTower(currPlayer) && backBone[column]->move()){
		int k = 0;
		for(k = 0; k < 3; ++k){
			if(towerLocation[k] == column) break;
		}
		// if it is a new column:
		if(k == 3){
			towerLocation[towerCounter] = column;
			++towerCounter; // increment counter.
		}
		// else, don't need to change anything.
	}
	return true;
};

void Board::
stop(){
	for(int k = 0; k < 3; ++k){
		if(towerLocation[k] != 0) backBone[towerLocation[k]]->stop(currPlayer);
	}
};

void Board::
bust(){
	for(int k = 0; k < 3; ++k){
		if(towerLocation[k] != 0) backBone[towerLocation[k]]->bust();
		towerLocation[k] = 0;
	}
	towerCounter = 0;
};








