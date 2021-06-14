#include "Item.h"
Item::Item() {
	this->itemi = " ";
	this->wi = 0;
	this->pi = 0;
}
Item::Item(string itemi, double wi, double pi) {
	this->itemi = itemi;
	this->wi = wi;
	this->pi = pi;
}
void Item::set_itemi(string itemi) {
	this->itemi = itemi;
}
void Item::set_wi(double wi) {
	this->wi = wi;
}
void Item::set_pi(double pi) {
	this->pi = pi;
}
string Item::get_itemi() {
	return itemi;
}
double Item::get_wi() {
	return wi;
}
double Item::get_pi() {
	return pi;
}
double Item::get_den() {
	return pi / wi;
}