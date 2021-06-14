#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <iomanip>
#include <fstream>
#include "Item.h"
using namespace std;
bool compareobj(Item a, Item b) {
	return a.get_den() > b.get_den();
}
vector<Item>sort_density(vector<Item>items) {
	sort(items.begin(), items.end(), compareobj);
	return items;
}
struct node {
    int level;
    double profit;
    double weight;
    double bound;
	vector<char> include;
};
struct cmp {
	bool operator()(node a, node b) {
		return a.bound < b.bound;
	}
};
vector<Item> read_items(string fName, double& W) {
	ifstream file;
	vector<Item>items;
	Item temp;
	file.open(fName);
	string itemi, comment;
	double wi, pi;
	file >> W;
	getline(file, comment);
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
double bound(vector<Item>items, double W, node u) {
	int j, k;
	double totw;
	double result;
	if (u.weight >= W)
		return 0;
	else {
		result = u.profit;
		j = u.level;
		totw = u.weight;
		while (j < items.size() && totw + items[j].get_wi() <= W) {
			totw = totw + items[j].get_wi();
			result = result + items[j].get_pi();
			j++;
		}
		k = j;
		if (k < items.size()) {
			result = result + (W - totw) * items[k].get_den();
		}
	}
	return result;
}

vector<char> knapsack3(vector<Item>items, double W, double& maxprofit) {
	vector<char>result;
	result.resize(items.size(),'n');
	priority_queue<node,vector<node>,cmp>PQ;
	vector<double>w;
	w.resize(items.size() + 1);
	for (int i = 0; i < items.size(); i++) {
		w[i + 1] = items[i].get_wi();
	}
	vector<double>p;
	p.resize(items.size() + 1);
	for (int i = 0; i < items.size(); i++) {
		p[i + 1] = items[i].get_pi();
	}
	node u;
	node k;
	node v;
	while (!PQ.empty()) {
		PQ.pop();
	}
	v.level = 0;  v.profit = 0; v.weight = 0;
	maxprofit = 0;
	v.bound = bound(items,W,v);
	v.include.resize(items.size(),'n');
	u.include.resize(items.size(),'n');
	k.include.resize(items.size(), 'n');
	PQ.push(v);
	double maxp = 0;
	while (!PQ.empty()) {
		v = PQ.top();
		//cout << "PQ사이즈" << PQ.size() << endl;
		//cout << "탑" << v.level << " "<<v.profit <<" "<< v.weight <<" "<< v.bound << endl;
		//for (int i = 0; i < result.size(); i++)
			//cout << result[i];
		PQ.pop();
		if (v.bound > maxprofit) {
			u.level = v.level + 1;
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			for (int i = 0; i<k.include.size(); i++)
				u.include[i] = v.include[i];
			if (u.weight <= W && u.profit > maxprofit) {
				maxprofit = u.profit;
				//cout << "최적" << u.level << " " << u.profit << " " << u.weight << " " << endl;
				if (u.profit > maxp) {
					//cout << "최고값갱신" << endl;
					u.include[u.level - 1] = 'y';
					for (int i = 0; i < u.include.size(); i++)
						result[i] = u.include[i];
				/*	for (int i = 0; i < result.size(); i++)
						cout << result[i];
					cout << "----------------------------" << endl;*/
				}
			}
			u.bound = bound(items, W, u);
			if (u.bound > maxprofit) {
				u.include[u.level - 1] = 'y';
				PQ.push(u);
				/*cout << "들어간PQ1:" << u.level << " " << u.weight << " " << u.profit << " " << u.bound << endl;
				for (int i = 0; i < u.include.size(); i++)
					cout <<u.include[i];*/
			}
			k.level = u.level;
			k.weight = v.weight;
			k.profit = v.profit;
			for (int i = 0;i< k.include.size(); i++)
				k.include[i] = v.include[i];
			k.bound = bound(items, W, k);
			if (k.bound > maxprofit) {
				k.include[k.level-1] = 'n';
				PQ.push(k);
				/*for (int i = 0; i < k.include.size(); i++)
					cout << k.include[i];
				cout << "들어간PQ2:" << k.level << " " << k.weight << " " << k.profit << " " << k.bound << endl;*/
			}
		}
	}
	return result;
}
vector<Item>select(vector<Item>items,vector<char>selected) {
	vector<Item>result;
	for (int i = 0; i < selected.size(); i++) {
		if (selected[i] == 'y') {
			result.push_back(items[i]);
		}
	}
	return result;
}
void print_items(vector<Item>items) {
	double wi_sum = 0, pi_sum = 0;
	cout << right << setw(10) << "물건" << right << setw(14) << "무게" << right << setw(14) << "이윤" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < items.size(); i++) {
		wi_sum += items[i].get_wi();
		pi_sum += items[i].get_pi();
		cout << left << setw(12) << items[i].get_itemi() << right << setw(16) << items[i].get_wi() << right << setw(16) << items[i].get_pi() << endl;
	}
	cout << "--------------------------------------------" << endl;
	cout << right << setw(9) << "계" << right << setw(19) << wi_sum << right << setw(16) << pi_sum << endl;
}
int main(){
	double W = 0;
	vector<Item>items = read_items("item.txt", W);
	vector<Item>sorted_items = sort_density(items);
	cout << W << endl;
	for (int i = 0; i < sorted_items.size(); i++) {
		cout << sorted_items[i].get_itemi() << " " << sorted_items[i].get_wi() << " " << sorted_items[i].get_pi() << endl;
	}
	cout << "--------------------------------------------" << endl;
	double maxprofit;
	vector<char>result=knapsack3(sorted_items, W, maxprofit);
	/*for (int i = 0; i<result.size(); i++)
		cout << result[i];*/
	vector<Item>select_items = select(sorted_items, result);
	/*for (int i = 0; i < select_items.size(); i++)
		cout << select_items[i].get_itemi() << " ";*/
	print_items(select_items);
}

