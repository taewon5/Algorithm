#include <iostream>
#include <string>
using namespace std;
class Nfa
{
	string fr;
	string to;
	string symbol;
public:
	Nfa();
	Nfa(string fr,string to, int symbol);
	void setfr(string fr);
	void setto(string to);
	void setsymbol(string symbol);
	string getfr();
	string getto();
	string getsymbol();
};

