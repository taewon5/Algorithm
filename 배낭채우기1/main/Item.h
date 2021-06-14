#include <iostream>
#include <string>
using namespace std;
class Item
{
	string itemi;
	double wi;
	double pi;
public:
	Item();
	Item(string itemi, double wi, double pi);
	void set_itemi(string itemi);
	void set_wi(double wi);
	void set_pi(double pi);
	string get_itemi();
	double get_wi();
	double get_pi();
	double get_den();
};

