#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <fstream>
#include "Edge.h"
using namespace std;
vector<vector<int>>subset(vector<string>inodes){
	vector<vector<int>>temp;
	int i, j;
	int n = inodes.size();
	temp.resize(pow(2,n));
	int max = 1 << n;
	for (i = 1; i < max; i++) {
		for (j = 1; j < n; j++) {
			if (i & (1 << j)) {
				temp[i].push_back(j);
			}
		}
	}
	return temp;
}
vector<Edge> read_edges(string fName) {
	ifstream file;
	vector<Edge>edge;
	Edge result;
	file.open(fName);
	string fr;
	string to;
	string wet1;
	string trash;
	double wet;
	while (!file.eof()) {
		getline(file, fr, ' ');
		result.set_fr(fr);
		getline(file, to, ' ');
		result.set_to(to);
		file >> wet;
		getline(file,trash, '\n');
		result.set_wet(wet);
		edge.push_back(result);
	}
	return edge;
}
map<string, int> make_node(vector<Edge>edges) {
	map<string, int>node;
	int j = 0;
	for (int i = 0; i < edges.size(); i++) {
		node.insert(pair<string, int>(edges[i].get_fr(), 0));
		node.insert(pair<string, int>(edges[i].get_to(), 0));
	}
	  for (auto it = node.begin(); it != node.end(); it++) {
		node.at(it->first) = j;
		j++;
	}
	return node;
}
vector<string>make_inode(map<string, int>nodes) {
	vector<string>inode;
	inode.resize(nodes.size());
	for (map<string,int>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		inode[it->second] = it->first;
	}
	return inode;
}
vector<vector<double>>makeGraph(vector<Edge>edges, map<string, int>nodes) {
	vector<vector<double>>graph;
	int n = nodes.size();
	for (int i = 0; i < n; i++) {
		vector<double>row;
		row.resize(n,99999);
		graph.push_back(row);
	}
	for (int i = 0; i < n; i++) {
			graph[i][i] = 0;
	}
	for (int i = 0; i < edges.size(); i++) {
		if (nodes.count(edges[i].get_fr()) == 1&&nodes.count(edges[i].get_to())==1) {
			map<string, int>::iterator iter;
			iter = nodes.find(edges[i].get_fr());
			int row = iter->second;
			iter = nodes.find(edges[i].get_to());
			int col = iter->second;
			graph[row][col] = edges[i].get_wet();
		}
	}
	return graph;
}
void travel(vector<vector<double>>W, map<string, int>nodes, vector<string>inodes) {
	vector<vector<int>>subsets=subset(inodes);
	int n = inodes.size();
	vector<Edge>result;
	int i, j, k;
	map<pair<int, vector<int>>, double>D;
	vector<vector<int>>P;
	P.resize(n);
	for (i = 0; i < P.size(); i++) {
		P[i].resize(n);
	}
	map<pair<int, vector<int>>, double>::iterator it;
	for (i = 1; i < n; i++) {
		D[{i, { 0 }}] = W[i][0];
	}
	for (k = 2; k <= n - 1; k++) {
		for (int s = 1; s < subsets.size(); s++) {
			if (k == 2&& subsets[s].size()==2) {
				D[{subsets[s][0], { subsets[s][1] }}] = D[{subsets[s][1], { 0 }}] + W[subsets[s][0]][subsets[s][1]];
				D[{subsets[s][1], { subsets[s][0] }}] = D[{subsets[s][0], { 0 }}] + W[subsets[s][1]][subsets[s][0]];
			}
			else if (k == 3 && subsets[s].size() == 3) {
				for (int i = 0; i < subsets[s].size(); i++) {
					//double minimum = min(W[subsets[s][i % 3]][subsets[s][(i + 1) % 3]]+W[subsets[s][(i + 1) % 3]][subsets[s][(i + 2) % 3]] + D[{subsets[s][(i + 2) % 3], { 0 }}], 
					//W[subsets[s][i % 3]][subsets[s][(i + 2) % 3]] + W[subsets[s][(i + 2) % 3]][subsets[s][(i + 1) % 3]] + D[{subsets[s][(i + 1) % 3], { 0 }}]);
					//D[{subsets[s][i % 3], { subsets[s][(i + 1) % 3], subsets[s][(i + 2) % 3] }}] = minimum;
					double D1 = W[subsets[s][i % 3]][subsets[s][(i + 1) % 3]] + W[subsets[s][(i + 1) % 3]][subsets[s][(i + 2) % 3]] + D[{subsets[s][(i + 2) % 3], { 0 }}];
					double D2 = W[subsets[s][i % 3]][subsets[s][(i + 2) % 3]] + W[subsets[s][(i + 2) % 3]][subsets[s][(i + 1) % 3]] + D[{subsets[s][(i + 1) % 3], { 0 }}];
					if (D1 < D2) {
						D[{subsets[s][i % 3], { subsets[s][(i + 1) % 3], subsets[s][(i + 2) % 3] }}] = D1;
						P[subsets[s][i % 3]][subsets[s][(i + 1) % 3]] = subsets[s][(i + 1) % 3];
						P[subsets[s][(i + 1) % 3]][subsets[s][(i + 1) % 3]]= subsets[s][(i + 2) % 3];
				 }
					else {
						D[{subsets[s][i % 3], { subsets[s][(i + 1) % 3], subsets[s][(i + 2) % 3] }}] = D2;
						P[subsets[s][i % 3]][subsets[s][(i + 1) % 3]] = subsets[s][(i + 2) % 3];
						P[subsets[s][(i + 1) % 3]][subsets[s][(i + 1) % 3]] = subsets[s][(i + 1) % 3];
					}
				}
			}
		}
	}
	double minlength =9999999;
	int minj = 0;
	for (int i = 1; i < n; i++) {
		if (minlength > (W[0][i % 3+1] + D[{i % 3+1, { (i + 1) % 3+1, (i + 2) % 3+1 }}])) {
		minlength = W[0][i % 3+1] + D[{i % 3+1, { (i + 1) % 3+1, (i + 2) % 3+1 }}];
		minj = i % 3+1;
		P[0][minj] = i%3+1;
	}
	}
	cout << "최단거리:" << minlength << endl;
	cout << inodes[0] << " " << inodes[P[0][minj]] << " " << inodes[P[minj][minj + 1 % 3]] << " " << inodes[P[minj + 1 % 3][minj + 1 % 3]]<<" "<< inodes[0]<<endl;
}

int main()
{
	cout << "-----------------------edges---------------------" << endl;
	vector<Edge>edges = read_edges("graph.txt");
	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].get_fr() << " " << edges[i].get_to() << " " << edges[i].get_wet() << endl;
	}

	map<string, int>nodes = make_node(edges);

	vector<string>inodes = make_inode(nodes);

	cout << "------------------------W배열--------------------------------------------------------" << endl;
	vector<vector<double>>W = makeGraph(edges, nodes);
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.size(); j++)
			cout << W[i][j] << "\t\t";
		cout << endl;
	}
	cout << "------------------------TSP--------------------------------------------------------" << endl;
 travel(W,nodes, inodes);
 system("pause");
}


