#ifndef Score_hpp
#define Score_hpp

#include <fstream>
#include <iomanip>
#include "tools.hpp"

class Score{
private:
	int Info[13] = {0};
public:
	Score();
	ostream& print(ostream& out);
	void update(int, const int*);
	void serialize(ostream& out);
	void realize(istream& in);

	// modified functions for p11.
	//int* getInfo(){return Info;};
	void appInfo(int c_no){++Info[c_no];};

};

inline ostream& operator << (ostream& out, Score& score){ return score.print(out); };

#endif