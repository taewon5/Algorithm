#include <iostream>
#include <vector>
#include <string>
#include "Key.h"
using namespace std;
Key::Key() {
	this->name = " ";
	this->num = 0;
}
Key::Key(string name, double num) {
	this->name = name;
	this->num = num;
}
void Key::setname(string name) {
	this->name = name;
}
void Key::setnum(double num) {
	this->num = num;
}
string Key::getname() {
	return name;
}
double Key::getnum() {
	return num;
}
bool Key:: operator <(Key& a) {
	return this->num > a.num;
}

