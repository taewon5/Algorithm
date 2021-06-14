#include <iostream>
#include <string>
#include<fstream>
#include<vector>
#include "Set.h"
using namespace std;

vector<Set>read_set(string fName,int &n,int &W) {
	ifstream file;
	vector<Set>sets;
	Set temp;
	file.open(fName);
	string name,comment;
	int wi;
	file >> n;
	getline(file, comment);
	file >> W;
	getline(file, comment);
	while (!file.eof()) {
		file >> name;
		temp.setname(name);
		file >> wi;
		temp.setwi(wi);
		sets.push_back(temp);
	}
	return sets;
}
bool promising(int w, int total, int W, vector<Set>sets, int i) {
	return (w + total >= W) && (w == W || w + sets[i+1].getwi() <= W);
}
void sum_of_subsets(vector<int>index,vector<Set>sets, int i,int w, int total,int W) {
	if (promising(w,total,W,sets,i)) {
		if (w == W) {
			for (int j = 0; j < index.size();j++) {
				if (index[j] == 1) {
					cout << sets[j].getname();
				}
				//cout << index[j];
			}
			cout<<endl;
		}
		else {
			index[i+1 ] = 1;
			sum_of_subsets(index, sets, i + 1, w + sets[i+1 ].getwi(), total - sets[i+1 ].getwi(),W);
			index[i+1 ] = 0;
			sum_of_subsets(index, sets, i + 1, w , total - sets[i+1 ].getwi(), W);
		}
	}
}

int main(){
	int n = 0;
	int W = 0;
	int total = 0;
    vector<Set>sets = read_set("input.txt",n,W);
	//cout << n << " " << W << endl;
	for (int i = 0; i < sets.size(); i++) {
		//cout << sets[i].getname() << " " << sets[i].getwi() << endl;
		total += sets[i].getwi();
	}
	cout << "------------------------------" << endl;
	vector<int>index;//인덱스를 이진수배열처럼 만듦
	index.resize(sets.size());//00000
	sum_of_subsets(index,sets ,-1,0, total,W);
	cout << "------------------------------" << endl;
}

