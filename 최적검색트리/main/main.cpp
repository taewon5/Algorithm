#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Key.h"
using namespace std;
struct node {
    string key;
    node* left;
    node* right;
    node() {
        this->key = " ";
        this->left = NULL;
        this->right = NULL;
    }
};

template<class T1, class T2>
vector<vector<T1>>make_matrix(vector<T2>& L) {
    vector<vector<T1>>M;
    int i;
    for (i = 0; i <= L.size(); i++) {
        vector<T1>row(L.size() + 1, 0);
        M.push_back(row);
    }
    vector<T1>row(L.size() + 1, 0);
    M.push_back(row);
    return M;
}

double Psum(vector<double>P, int a, int b) {
    double sum = 0;
    for (int i = a; i <= b; i++) {
        sum += P[i];
    }
    return sum;
}
vector<Key> read_keys(string Fname) {
    vector<Key>keys;
    Key temp;
    ifstream file;
    string name;
    double num;
    file.open(Fname);
    while (!file.eof()) {
        file >> name;
        file >> num;
        temp.setname(name);
        temp.setnum(num);
        keys.push_back(temp);
    }
    file.close();
    return keys;
}
double  optsearchtree(vector<Key>keys, vector<vector<double>>& A, vector<vector<int>>& R) {
    int n = keys.size();
    int i, j, k, diagonal;
    double minavg = 0;
    vector<double>P;
    P.resize(n + 1, 0);
    for (i = 1; i <= n; i++) {
        P[i] = keys[i - 1].getnum();
    }
    for (i = 1; i <= n; i++) {
        A[i][i - 1] = 0;
        A[i][i] = P[i];
        R[i][i] = i;
        R[i][i - 1] = 0;
    }
    A[n + 1][n] = 0;
    R[n + 1][n] = 0;
    for (diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            double sum = Psum(P, i, j);
            double min = 10000000;
            for (k = i; k <= j; k++) {
                if (min >= A[i][k - 1] + A[k + 1][j] + sum) {
                    min = A[i][k - 1] + A[k + 1][j] + sum;
                    R[i][j] = k;
                }
            }
            A[i][j] = min;
        }
        minavg = A[1][n];
    }

    return minavg;
}
node* make_node(string key) {
    node* p = new node;
    p->key = key;
    cout << p->key;
    p->left = NULL;
    p->right = NULL;
    return p;
}
node* tree(int i, int j, vector<Key>keys, vector<vector<int>>R) {
    int k = 0;
    node* p;
    k = R[i][j];
    if (k == 0)
        return NULL;
    else {
        p = make_node(keys[k - 1].getname());
        cout << endl;
        cout << "\t";
        p->left = tree(i, k - 1, keys, R);
        cout << "\t";
        p->right = tree(k + 1, j, keys, R);
    }
}
void print_tree(int n, node* root) {
    if (root != NULL)
    {
        for (int i = 0; i <= n; i++)
            cout << "\t";
        cout << root->key;
        cout << endl;
        print_tree(n + 1, root->left);
        print_tree(n + 1, root->right);
    }
}
int main()
{
    vector<Key>keys = read_keys("keys.txt");
    sort(keys.begin(), keys.end());
    vector<vector<double>>A = make_matrix<double, Key>(keys);
    vector<vector<int>>R = make_matrix<int, Key>(keys);

    double minavg = optsearchtree(keys, A, R);
    node* root = tree(1, keys.size(), keys, R);
    print_tree(0, root);

    return 1;
}