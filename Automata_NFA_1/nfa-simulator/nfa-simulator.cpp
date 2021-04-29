#include "Nfa.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
vector<Nfa> read_nfa(string Fname,string& starting,vector<string>&finalstate) {
    vector<Nfa>states;
    vector<string>symbols;
    Nfa temp;
    ifstream file;
    string fr,to,symbol;
    char j;
    file.open(Fname);
    getline(file, starting);
    while (1) {
        file >> to;
        finalstate.push_back(to);
        file.get(j);
        if (j == '\n') {
            break;
        }
    }
    j = ' ';
    while (1) {
        file >> symbol;
        symbols.push_back(symbol);
        file.get(j);
        if (j == '\n') {
            break;
        }
    }
    while (!file.eof()) {
        file >> fr >> symbol >> to;
        temp.setfr(fr);
        temp.setsymbol(symbol);
        temp.setto(to);
        states.push_back(temp);
    }
    file.close();
    return states;
}
vector<vector<string>> read_input(string Fname) {
    vector<vector<string>> inputs;
    vector<string>temp;
    string input;
    ifstream file;
    file.open(Fname);
    char j;
    while (!file.eof()) {
        j = ' ';
        while (1) {
            file >> input;
            temp.push_back(input);
            file.get(j);
            if (j == '\n' || file.eof()) {
                inputs.push_back(temp);
                break;
            }
        }
        temp.clear();
    }
  return inputs;
}
vector<string> simulate(vector<Nfa>states, vector<vector<string>>inputs,string starting, vector<string>finalstate) {
    int i, j, k;
    vector<string>result;
    result.resize(inputs.size());
    string locate1,locate2;
    for (i = 0; i < inputs.size(); i++) {
        locate1 = starting;
        locate2 = starting;
        result[i] = "No";
        for (j = 0; j < inputs[i].size(); j++) {
            for (k = 0; k < states.size(); k++) {        
                if (locate1 == states[k].getfr() && states[k].getsymbol() == inputs[i][j]) {
                    locate2 = states[k].getto();
                    locate1 = locate2;
                    break;
                }
            }
            if (j==inputs[i].size()-1 &&finalstate.size()!=find(finalstate.begin(), finalstate.end(),locate1)- finalstate.begin()){
                result[i] = "Yes";
             }
        }
    }
    return result;
}
int main() {
	string starting;
	vector<string>finalstate;
	vector<Nfa>states = read_nfa("nfa.txt", starting, finalstate); //nfa입력

	cout << starting << endl;
	for (int i = 0; i < finalstate.size(); i++) {
		cout << finalstate[i] << endl;
	}
	for (int i = 0; i < states.size(); i++) {
		cout << states[i].getfr() << " " << states[i].getsymbol() << " " << states[i].getto() << endl;
	}
	vector<vector<string>>inputs = read_input("input.txt"); //input 입력

	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 0; j < inputs[i].size(); j++) {
			cout << inputs[i][j] << " ";
		}
        cout << endl;
	}
    cout << "--------------------------" << endl;
    vector<string>result=simulate(states, inputs,starting,finalstate);

    for (int i = 0; i < inputs.size(); i++) {
        for (int j = 0; j < inputs[i].size(); j++) {
            cout << inputs[i][j] << " ";
        }
        cout <<" -> "<<result[i]<< endl;
    }
}
            
