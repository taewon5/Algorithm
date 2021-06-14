#include "Minfo.h"
#include <string>
#include <iostream>
using namespace std;

Minfo::Minfo() {
	name = " ";
	row = 0;
	column = 0;
}
Minfo::Minfo(string name, int row, int column) {
	this->name = name;
	this->row = row;
	this->column = column;
}
void Minfo::setname(string name) {
	this->name = name;
}
void Minfo::setrow(int row) {
	this->row = row;
}
void Minfo::setcolumn(int column) {
	this->column = column;
}
string Minfo::getname() {
	return name;
}
int Minfo::getrow() {
	return row;
}
int Minfo::getcolumn() {
	return column;
}
