#pragma once
#include <string>
#include <iostream>
using namespace std;

class Minfo
{
	string name;
	int row;
	int column;
public:
	Minfo();
	Minfo(string name, int row, int column);
	void setname(string name);
	void setrow(int row);
	void setcolumn(int column);
	string getname();
	int getrow();
	int getcolumn();
};

