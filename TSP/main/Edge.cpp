#include "Edge.h"
Edge::Edge() {
	this->to= " ";
	this->fr = " ";
	this->wet = 0;
}
Edge::Edge(string to, string fr, double wet) {
	this->to = to;
	this->fr = fr;
	this->wet = wet;
}
void Edge::set_to(string to) {
	this->to = to;
}
void Edge::set_fr(string fr) {
	this->fr = fr;
}
void Edge::set_wet(double wet) {
	this->wet = wet;
}
string Edge::get_to() {
	return to;
}
string Edge::get_fr() {
	return fr;
}
double Edge::get_wet() {
	return wet;
}