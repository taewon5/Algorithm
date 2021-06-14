#include "Circuit.h"
Circuit::Circuit() {
	this->fr = " ";
	this->to = " ";
}
Circuit::Circuit(string fr, string to) {
	this->fr = fr;
	this->to = to;
}
void Circuit::setfr(string fr) {
	this->fr = fr;
}
void Circuit::setto(string to) {
	this->to = to;
}
string Circuit::getfr() {
	return fr;
}
string Circuit::getto() {
	return to;
}
