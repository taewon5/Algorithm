#pragma once
#include <iostream>
#include <string>
using namespace std;
class Circuit
{
	string fr;
	string to;
public:
	Circuit();
	Circuit(string fr, string to);
	void setfr(string fr);
	void setto(string to);
	string getfr();
	string getto();
};

