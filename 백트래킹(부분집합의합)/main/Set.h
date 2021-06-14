#include <iostream>
#include <string>
using namespace std;
class Set
{
	string name;
	int wi;
public:
	Set();
	Set(string name, int wi);
	void setname(string name);
	void setwi(int wi);
	string getname();
	int getwi();
};

