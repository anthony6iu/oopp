#ifndef ScoreBoard_hpp
#define ScoreBoard_hpp

#include <fstream>
#include <map>
#include <utility>

#include "tools.hpp"
#include "Score.hpp"
#include <string>
#include <iomanip>

#define SBoard map<char*, Score>
#define SBpair pair<char*, Score>

#define INF  "./SBinput.txt"
#define OUTF "./SBoutput.txt"

class ScoreBoard:public SBoard{
private:
	SBoard SBm;
	//SBpair SBp;
public:
	ScoreBoard();
	~ScoreBoard();
	void realize();
	void serialize();
	void update(const char* Name, const int* columns);
	ostream& print(ostream&);	
};
inline ostream& operator << (ostream& out, ScoreBoard& scoreboard){ return scoreboard.print(out); };
#endif
