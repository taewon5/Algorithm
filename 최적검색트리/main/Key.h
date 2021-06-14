#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Key
{
	string name;
	double num;
public:
	Key();
	Key(string name, double num);
	void setname(string name);
	void setnum(double num);
	string getname();
	double getnum();
	bool operator <(Key& a);
};

