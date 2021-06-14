#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <map>
#include <fstream>
#include "Edge.h"
using namespace std;
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
		getline(file, fr, '#');
		result.set_fr(fr);
		getline(file, to, '#');
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
		row.resize(n,INT_MAX);
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
			graph[col][row] = edges[i].get_wet();
		}
	}
	return graph;
}
vector<Edge>prim(vector<vector<double>>W, vector<string>inodes) {
	int i, vnear;
	int n = W.size();
	double min;
	Edge result;
	vector<Edge>F;
	vector<int>nearest;
	vector<double>distance;
	nearest.resize(n);
	distance.resize(n);
	for (i = 1; i < n; i++) {
		nearest[i] = 0;
		distance[i] = W[0][i];
	}
	for (int j = 1; j < n; j++) {
		min = INT_MAX;
		for (i = 1; i < n; i++) {
			if (distance[i] >= 0 && distance[i] < min) {
				min = distance[i];
				vnear = i;
			}
		}
		string to =inodes[vnear];
		string fr = inodes[nearest[vnear]];
		double wet = min;
		result.set_fr(fr);
		result.set_to(to);
		result.set_wet(wet);
		F.push_back(result);
		distance[vnear] = -1;
		for (i = 1; i < n; i++) {
			if (W[i][vnear] < distance[i]) {
				distance[i] = W[i][vnear];
				nearest[i] = vnear;
			}
		}
	}
	return F;
}
int main()
{
	cout << "-----------------------edges---------------------" << endl;
	vector<Edge>edges = read_edges("graph.txt");
	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].get_fr() << " " << edges[i].get_to() << " " << edges[i].get_wet() << endl;
	}
	cout << "-----------------------nodes---------------------" << endl;
	map<string, int>nodes = make_node(edges);
	for (map<string, int>::iterator it =nodes.begin();it!=nodes.end();it++){
		cout << it->first << " " << it->second << endl;
	}
	cout << "------------------------inodes--------------------" << endl;
	vector<string>inodes = make_inode(nodes);
	for (int i = 0; i < inodes.size(); i++) {
		cout <<i<<" "<< inodes[i] << endl;
	}
	cout << "------------------------W배열--------------------------------------------------------" << endl;
	vector<vector<double>>W = makeGraph(edges, nodes);
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.size(); j++)
			cout << W[i][j] << "\t\t";
		cout << endl;
	}
	cout << "----------------------------------F벡터------------------------------------------------" << endl;

	vector<Edge>F = prim(W, inodes);
	for (int i = 0; i < F.size(); i++) {
		cout << i<<" "<<F[i].get_fr() << " " << F[i].get_to() << " " << F[i].get_wet() << endl;
	}
}


