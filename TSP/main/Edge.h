#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Edge
{
	string fr;
	string to;
	double wet;
public:
	Edge();
	Edge(string fr, string to, double wet);
	string get_fr();
	string get_to();
	double get_wet();
	void set_fr(string fr);
	void set_to(string to);
	void set_wet(double wet);
};

