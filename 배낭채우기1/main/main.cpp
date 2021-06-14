#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <algorithm>
#include <iomanip>
#include "Item.h"
using namespace std;
bool compareobj(Item a, Item b) {
	return a.get_den() > b.get_den();
}
vector<Item>sort_density(vector<Item>items) {
	sort(items.begin(), items.end(), compareobj);
	return items;
}
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
vector<Item>Knapsack(vector<Item>items, double W) { //무게당 가치가 가장 높은순으로 담는다. 남는 무게는 쪼개서 넣는다.
	vector<Item> result;
	vector<Item>sorted_items = sort_density(items);
	double count_wi=0;
	double Fraction=0;
	for (int i = 0; i < sorted_items.size(); i++) {
		count_wi += sorted_items[i].get_wi();
		if (count_wi <= W) {
			result.push_back(sorted_items[i]);
		}
		else if(W-count_wi+sorted_items[i].get_wi() >0){
			Fraction = (W - (count_wi- sorted_items[i].get_wi())) / sorted_items[i].get_wi();
			double  fraction_wi = W - (count_wi - sorted_items[i].get_wi());
			double  fraction_pi = sorted_items[i].get_pi() * Fraction;
			result.push_back(Item(sorted_items[i].get_itemi(), fraction_wi, fraction_pi));
		}
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
	items= sort_density(items);
	for (int i = 0; i < items.size(); i++) {
		cout << items[i].get_itemi() << " " << items[i].get_wi() << " " << items[i].get_pi() << endl;
	}
	cout << "--------------------------------------------" << endl;
	vector<Item>selected_items = Knapsack(items, W);
	print_items(selected_items);
}
