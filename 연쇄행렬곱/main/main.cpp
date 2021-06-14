#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits.h>
#include "Minfo.h"
using namespace std;
vector<Minfo> read_matrix_info(string Fname) {
    vector<Minfo>mats;
    Minfo temp;
    ifstream file;
    string name;
    int row, col;
    file.open(Fname);
    while (!file.eof()) {
        file >> name;
        file >> row >> col;
        temp.setname(name);
        temp.setrow(row);
        temp.setcolumn(col);
        mats.push_back(temp);
    }
    file.close();
    return mats;
}
vector<int> make_dimensions(vector<Minfo> mats) {
    vector<int>d;
    int n = mats.size() + 1;
    d.resize(n);
    d[0] = mats[0].getrow();
    for (int i = 1; i < n; i++)
        d[i] = mats[i - 1].getcolumn();
    return d;
}
vector<vector<int>> make_matrix(vector<Minfo> mats) {
    vector<vector<int>>matrix;
    int n = mats.size() + 1;  //책에나오는 인덱스 방식을 쓰기위해 행과열을 1크게 만듦
    for (int i = 0; i < n; i++) {
        vector<int>element;
        element.resize(n);
        matrix.push_back(element);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    return matrix;
}
void minmulti(vector<int> d, vector<vector<int>>& M, vector<vector<int>>& P) {
    int  i, j, k, diagonal, min_temp;
    int min_k = 0;
    int n = d.size() - 1;

    for (diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            int min = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                min_temp = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (min > min_temp) {
                    min = min_temp;
                    min_k = k;
                }
            }
            M[i][j] = min;
            P[i][j] = min_k;
        }
    }
}
void clear_matrix(vector<vector<int>>& M) {
    int  n = M.size();
    for (int row = 0; row < n; ++row) {
        M[row].clear();
    }
    M.clear();
}
void order(int i, int j, vector<vector<int>>& P, vector<Minfo>& mats) {
    int k;
    if (i == j)
        cout << mats[i - 1].getname();
    else {
        k = P[i][j];
        cout << "(";
        order(i, k, P, mats);
        order(k + 1, j, P, mats);
        cout << ")";
    }
}
int main()
{
    vector<Minfo>mats = read_matrix_info("num.txt");
    vector<int>d = make_dimensions(mats);
    vector<vector<int>>M = make_matrix(mats);
    vector<vector<int>>P = make_matrix(mats);

    minmulti(d, M, P);
    order(1, d.size() - 1, P, mats);

    clear_matrix(M);
    clear_matrix(P);
    return 1;
}

