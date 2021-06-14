#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include "Item.h"
using namespace std;
vector<Item> read_items(string fName, double& W) {
	ifstream file;
	vector<Item>items;
	Item temp;
	file.open(fName);
	string itemi,comment;
	double wi, pi;
	file >> W;
	getline(file,comment);
	getline(file, comment);
	while (!file.eof()) {
		file >> itemi;
		temp.set_itemi(itemi);
		file >> wi >> pi;
		temp.set_wi(wi);
		temp.set_pi(pi);
		items.push_back(temp);
	}
	return items;
}
vector<Item>Knapsack(vector<Item>items, double W, double& max_pi) {
	vector<Item> result;
	vector<vector<double>>P;
	vector<vector<int>>index;
	P.resize(items.size() + 1);
	index.resize(items.size() + 1);
	for (int i = 0; i < P.size(); i++) {
		P[i].resize(W + 1);
		index[i].resize(W+1);
}
	for (int i = 0; i < P.size() - 1; i++) {
		 for (int w = 0; w < W + 1; w++) {
			 index[i ][w] = 0;
			 if (items[i].get_wi() <= w) {
				 if (items[i].get_pi() + P[i][w - items[i].get_wi()] >= P[i][w]) {
					 P[i + 1][w] = items[i].get_pi() + P[i][w - items[i].get_wi()];
					 index[i ][w] = 1;
				 }
				 else{
					 P[i + 1][w] = P[i][w];
				 }
			 }
			 else
				 P[i + 1][w] = P[i][w];
		}
	}
	int i = P.size() - 1;
	int w = W;
	while (i != -1 && w != 0) {
		if (index[i][w]==1) {
			result.push_back(items[i]);
			w -= items[i].get_wi();
		}
		i--;
	}
	return result;
}
void print_items(vector<Item>items) {
	double wi_sum = 0,pi_sum=0;
	cout << right << setw(10) << "물건" << right << setw(14) << "무게" << right << setw(14) << "이윤" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < items.size(); i++) {
		wi_sum+=items[i].get_wi();
		pi_sum += items[i].get_pi();
		cout << left << setw(12) << items[i].get_itemi() << right << setw(16) << items[i].get_wi() << right << setw(16) << items[i].get_pi() << endl;
	}
	cout << "--------------------------------------------" << endl;
	cout << right << setw(9) << "계"<<right << setw(19) << wi_sum << right << setw(16) << pi_sum << endl;
}
int main(){
	double W = 0;
    vector<Item>items = read_items("item.txt",W);
	cout << W << endl;
	for (int i = 0; i < items.size(); i++) {
		cout << items[i].get_itemi() << " " << items[i].get_wi() << " " << items[i].get_pi() << endl;
	}
	cout << "--------------------------------------------" << endl;
	double max_pi;
	vector<Item>selected_items = Knapsack(items, W,max_pi);
	print_items(selected_items);
	system("pause");
}
