#include "Set.h"
Set::Set(){
	this->name = " ";
	this->wi = 0;
}
Set::Set(string name, int wi) {
	this->name = name;
	this->wi = wi;
}
void Set::setname(string name) {
	this->name = name;
}
void Set::setwi(int wi) {
	this->wi = wi;
}
string Set::getname() {
	return name;
}
int Set::getwi() {
	return wi;
}