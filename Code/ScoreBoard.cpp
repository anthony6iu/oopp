#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard(){
	// Create SBpair and inset into the map.
	/*
	Score sc;
	char key[] = "GAME";
	//SBp = make_pair(key,sc);
	
	SBp.first  = key;
	SBp.second = sc;
	SBm.insert(SBp);
	*/
	realize();

};

ScoreBoard::~ScoreBoard(){
	serialize();
}

void ScoreBoard::realize(){
	ifstream in(INF);
	if(!in.is_open()) fatal("Open SB input file failed.\n");
	// read from INF:
	while(in.good())
	{
		string pname;
		Score temp_score;
		in>>pname; // read player name.
		temp_score.realize(in); // read his column.

		// set SBpair:
		char* c_pname = new char[pname.size()];
		copy(pname.begin(),pname.end(),c_pname);
		if(strcmp(c_pname,"\0")) SBm.insert(make_pair(c_pname,temp_score));
	};
	in.close();

};

void ScoreBoard::serialize(){
	ofstream out(OUTF);
	if(!out.is_open()) fatal("Open SB output file failed.\n");

	// game time +1
	for(iterator ig = SBm.begin(); ig != SBm.end(); ++ig){
		if(!strcmp(ig->first,"GAME")) ig->second.appInfo(0); // update game play times.
	}
	
	// output player's info. one by one.
	for(iterator k = SBm.begin(); k != SBm.end(); ++k){
		out<<setw(14)<<k->first<<" ";
		k->second.serialize(out);
	}
	out.close();
};

void ScoreBoard::update(const char* name, const int* columns){
	// input colums is the current captured array.
	bool inlist = false;
	int cnt = 0;
	for(int n = 0; n < 3; ++n){
		if(columns[n] != 0) ++cnt;
	}

	// check player in list or not. 
	// if in list:
	for(iterator k = SBm.begin(); k != SBm.end(); ++k){
		if(!strcmp(k->first,name)){
			k->second.update(cnt,columns);
			inlist = true;
			break;
		}
	}
	// if not:
	if(!inlist){
		// set temp score object.
		Score temp_score;
		temp_score.update(cnt,columns);
		// set temp c_str player name.
		string s_name(name);
		char* temp_name = new char[s_name.size()];
		copy(s_name.begin(),s_name.end(),temp_name);
		// set SBpair and insert to current map.
		SBm.insert(make_pair(temp_name,temp_score));

	}

	int* game_array = NULL;
	// update to game info, first.
	for(iterator k = SBm.begin(); k != SBm.end(); ++k){
		if(!strcmp(k->first,"GAME")){
			for(int c = 0; c < cnt; ++c) k->second.appInfo(columns[c]);
			break;
		}
	} 		
	
};

ostream& ScoreBoard::print(ostream& out){
	for(iterator iter = SBm.begin(); iter != SBm.end(); ++iter){
		if(!strcmp(iter->first,"GAME")){
			out<<setw(13+15+1)<<"GAME Infos: "<<iter->second;
		}
		else{
			out<<"Player name: "<<setw(15)<<iter->first<<" ";
			out<<iter->second;
		}
	}
	return out;
};












