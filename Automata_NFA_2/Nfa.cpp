#include "Nfa.h"
#include <iostream>
#include <string>
using namespace std;
Nfa::Nfa() {
	this->fr = " ";
	this->to = " ";
	this->symbol =" ";
}
Nfa::Nfa(string fr,string to, int symbol) {
	this->fr = fr;
	this->to = to;
	this->symbol = symbol;
}
void Nfa::setfr(string fr) {
	this->fr = fr;
}
void Nfa::setto(string to) {
	this->to = to;
}
void Nfa::setsymbol(string symbol) {
	this->symbol = symbol;
}
string Nfa::getfr() {
	return fr;
}
string Nfa::getto() {
	return to;
}
string Nfa::getsymbol() {
	return symbol;
}