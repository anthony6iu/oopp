#include "Score.hpp"

Score::Score(){
	for(int a = 0; a < 13; ++a){
		Info[a] = 0;
	}
}

void Score::serialize(ostream& out){
	for(int a = 0; a < 13; ++a){
		if(a == 12) out<<Info[a];
		else out<<Info[a]<<" ";
	}
	out<<"\n";
}

void Score::update(int cnt, const int* columns){
    // update columns infos.
	for(int c = 0; c < cnt; ++c){
		++Info[columns[c]];
	}
	++Info[0]; // add play times.
	if(cnt == 3) ++Info[1]; // add won times. 
}

void Score::realize(istream& in){
	//
	for(int j = 0; j < 13; ++j){
		int temp;
		in>>temp;
		Info[j] = temp;
	}
}

ostream& Score::print(ostream& out){
	for(int j = 0; j < 13; ++j){
		if     (j == 0) out<<"GameTimes: " <<setw(2)<<Info[j]<<" ";
		else if(j == 1) out<<"WonTimes: "  <<setw(2)<<Info[j]<<" ";
		else            out<<"C"<<j<<": "  <<setw(2)<<Info[j]<<" ";
	}
	out<<endl;
	return out;
};



