#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Circuit.h"
const string DELMIT = " -> ";
using namespace std;
vector<Circuit> readCircuit(string fName, vector<string>& nodes) {
	ifstream file;
	vector<Circuit>Circuits;
	Circuit result;
	file.open(fName);
	string fr;
	string to;
	string node;
	char j;
	while (1) {
		file >> node;
		nodes.push_back(node);
		file.get(j);
		if (j == '\n') {
			break;
		}
	}
	while (!file.eof()) {
		file >> fr >> to;
		result.setfr(fr);
		result.setto(to);
		Circuits.push_back(result);
	}
	return Circuits;
}
map<string, int>makenode(vector<string>inodes) {
	map<string, int>nodes;
	for (int i = 0; i < inodes.size(); i++) {
		nodes[inodes[i]] = i;
	}
	return nodes;
}
vector<vector<int>>makeW( map<string, int>nodes, vector<Circuit>Circuits) {
	vector<vector<int>>W;
	int n = nodes.size();
	W.resize(n);
	for (int i = 0; i < n; i++) {
		W[i].resize(n);
	}
	for (int i = 0; i < Circuits.size(); i++) {
		if (nodes.count(Circuits[i].getfr()) == 1 && nodes.count(Circuits[i].getto()) == 1) {
			map<string, int>::iterator iter;
			iter = nodes.find(Circuits[i].getfr());
			int row = iter->second;
			iter = nodes.find(Circuits[i].getto());
			int col = iter->second;
			W[row][col] = 1;
			W[col][row] = 1;
		}
	}
	return W;
}
bool promising(vector<vector<int>>W, vector<string>inodes, vector<int>vindex, int i) {
	int j;
	bool ok;
	if (i == inodes.size() - 1 && !W[vindex[inodes.size() - 1]][vindex[0]])
		ok = false;
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
		ok = false;
	else {
		ok = true;
		j = 1;
		while (j < i && ok) {
			if (vindex[i] == vindex[j])
				ok = false;
			j++;
		}
	}
	return ok;
}
void hamiltonian(vector<vector<int>>W,vector<string>inodes,vector<int>vindex,int i) {
	int j;
	if (promising(W,inodes,vindex,i))
		if (i == inodes.size() - 1) {
			for (int i = 0; i < vindex.size() ; i++) {
				cout << inodes[vindex[i]] << DELMIT;
			}
			cout << inodes[0]<<endl;
		}
		else
			for (j = 1; j < inodes.size(); j++) {
				vindex[i + 1] = j;
				hamiltonian(W, inodes, vindex,i + 1);
			}
}
int main() {
	vector<string>inodes;
	vector<Circuit>Circuits = readCircuit("input.txt", inodes);
	for (int i = 0; i < inodes.size(); i++) {
		cout << inodes[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < Circuits.size(); i++) {
		cout << Circuits[i].getfr() << " " << Circuits[i].getto() << endl;
	}
	map<string, int>nodes = makenode(inodes);
	/*map<string, int>::iterator it;
	for (it=nodes.begin(); it!=nodes.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}*/
	vector<vector<int>>W = makeW(nodes, Circuits);
	/*for (int i = 0; i < W.size(); i++) {
		for (int j = 0; j < W[i].size(); j++) {
			cout << W[i][j] << " ";
		}
		cout << endl;
	}*/
	vector<int>vindex;
	vindex.resize(nodes.size());
	cout << "--------------------해밀튼회로--------------------" << endl;
	hamiltonian(W,inodes,vindex,0);
}
