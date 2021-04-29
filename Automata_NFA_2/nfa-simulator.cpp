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
void path(vector<Nfa>states, string state, string starting,string& result) {
    for (int i = 0; i < states.size(); i++) {
        if (states[i].getto() == state) {
            if (states[i].getfr() == starting) {
                result = "yes";
                break;
            }
            else {
                result = "no";
                path(states, states[i].getfr(), starting, result);
                break;
            }
        }
    }
}
string simulate(vector<Nfa>states,string starting, vector<string>finalstate) {
    string result;
    for (int i = 0; i < finalstate.size(); i++) {
        path(states, finalstate[i], starting, result);
        if (result == "yes")
            break;
   }
    return result;
}
int main() {
    string starting1, starting2;
	vector<string>finalstate1;
    vector<string>finalstate2;
	vector<Nfa>states1 = read_nfa("nfa1.txt", starting1, finalstate1); //nfa입력
    //vector<Nfa>states2 = read_nfa("nfa2.txt", starting2, finalstate2);
	cout << starting1 << endl;
	for (int i = 0; i < finalstate1.size(); i++) {
		cout << finalstate1[i] << endl;
	}
	for (int i = 0; i < states1.size(); i++) {
		cout << states1[i].getfr() << " " << states1[i].getsymbol() << " " << states1[i].getto() << endl;
	}
    /*cout << starting2 << endl;
    for (int i = 0; i < finalstate2.size(); i++) {
        cout << finalstate2[i] << endl;
    }
    for (int i = 0; i < states2.size(); i++) {
        cout << states2[i].getfr() << " " << states2[i].getsymbol() << " " << states2[i].getto() << endl;
    }*/
    cout << "--------------------------" << endl;
    string result1= simulate(states1, starting1, finalstate1);
    cout << result1 << endl;
    //string result2= simulate(states2, starting2, finalstate2);
    //cout << result2 << endl;
    system("pause");
}
            
