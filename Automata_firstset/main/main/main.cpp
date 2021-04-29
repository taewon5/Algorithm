#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include<fstream>
#include <algorithm>
#include<list>
using namespace std;
vector<vector<string>> read_term(string Fname, string& starting) {
    vector<vector<string>>states;
    vector<string>temp;
    ifstream file;
    string terminal;
    char j;
    file.open(Fname);
    getline(file, starting);
    while (!file.eof()) {
        j = ' ';
        while (1) {
            file >>terminal;
            temp.push_back(terminal);
            file.get(j);
            if (j == '\n' || file.eof()) {
                states.push_back(temp);
                break;
            }
        }
        temp.clear();
    }
    file.close();
    return states;
}
vector<vector<string>>first_set(vector<vector<string>>states,string starting, vector<string>nonterminal) {
    vector<vector<string>>result;
    result.resize(nonterminal.size());
    for (int i = 0; i < nonterminal.size(); i++) {
        result[i].push_back(nonterminal[i]);
    }
   vector<string>result2;
   vector<string>::iterator it;
   for (int i = 0; i < states.size(); i++) {
       it = find(nonterminal.begin(), nonterminal.end(), states[i][2]);
       if (it == nonterminal.end()) {
           it = find(nonterminal.begin(), nonterminal.end(), states[i][0]);
           result[distance(nonterminal.begin(), it)].push_back(states[i][2]);
           //result[distance(result.begin(), it)].push_back(states[i][2]);
           for (int j = 2; j < states[i].size(); j++) {
               it = find(nonterminal.begin(), nonterminal.end(), states[i][j]);
               if (it != nonterminal.end()) {
                   result[distance(nonterminal.begin(), it)].push_back(states[i][2]);
               }
           }
       }
   }
   vector<string>lamda;
   for (int i = 0; i < result.size(); i++) {
       for (int j = 1; j < result[i].size(); j++) {
           it=find(result[i].begin(), result[i].end(), "e");
           if (it != result[i].end()) {
               lamda.push_back(result[i][0]);
           }
       }
   }
   for (int i = 0; i < states.size(); i++) {
       it = find(nonterminal.begin(), nonterminal.end(), states[i][2]);
       if (it != nonterminal.end()) {
           it = find(lamda.begin(), lamda.end(), states[i][2]);
           if (it != lamda.end()) {
               for(int j=2;j<states[i].size();j++){
                   it = find(nonterminal.begin(), nonterminal.end(), states[i][j]);
                   if (it == nonterminal.end()) {
                       it= find(nonterminal.begin(), nonterminal.end(), states[i][0]);
                       result[distance(nonterminal.begin(), it)].push_back(states[i][j]);
                       break;
                   }
               }
           }
           else {
               it = find(nonterminal.begin(), nonterminal.end(), states[i][2]);
               vector<string>::iterator it2;
               it2 = find(nonterminal.begin(), nonterminal.end(), states[i][0]);
               for (int j = 1; j < result[distance(nonterminal.begin(), it)].size(); j++)
                   result[distance(nonterminal.begin(), it2)].push_back(result[distance(nonterminal.begin(), it)][j]);
           }
       }
   }
    return result;
}
int main(){
    string starting;
    vector<vector<string>>states = read_term("grammar1.txt", starting);
    cout << starting << endl;
    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j<states[i].size(); j++) {
            cout << states[i][j]<<" ";
        }
        cout << endl;
    }
    vector<string>nonterm;
    for (int i = 0; i < states.size(); i++) {
        nonterm.push_back(states[i][0]);
    }
    nonterm.erase(unique(nonterm.begin(), nonterm.end()), nonterm.end());
    cout << "----------------------------------"<<endl;
    vector<vector<string>>result=first_set(states, starting,nonterm);
    for (int i = 0; i < result.size(); i++) {
        result[i].erase(unique(result[i].begin(), result[i].end()), result[i].end());
        cout << result[i][0] << ": {";
        for (int j = 1; j < result[i].size(); j++) {
            cout << result[i][j]<< " ";
        }
        cout << "}"<< endl;
    }
    cout << " e 는 lamda" << endl;
    system("pause");
}
