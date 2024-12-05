#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void readData(vector<int> &leftCol, vector<int> &rightCol) {
    ifstream file("test.txt");
    if(!file.is_open()) {
        cerr << "Error Opening File" << endl;
        exit(-1);
    }

    int left, right;
    while (file >> left >> right) {
        leftCol.push_back(left);
        rightCol.push_back(right);
    }

    file.close();
}

int main() {
    vector<int> leftCol;
    vector<int> rightCol;
    readData(leftCol, rightCol);

    sort(leftCol.begin(), leftCol.end());
    sort(rightCol.begin(), rightCol.end());

    int totalDist = 0;
    for (int i = 0; i < leftCol.size(); i++) {
        totalDist += abs(leftCol[i]-rightCol[i]);
    }
    cout << totalDist << endl;

    return 0;
}