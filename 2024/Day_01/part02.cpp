#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
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

    // hash map of numer of times right elemnts occur
    unordered_map<int, int> rightOccurs;
    for (int i = 0; i < rightCol.size(); i++) {
        rightOccurs[rightCol[i]]++;
    }

    int similarityScore = 0;
    for (int i = 0; i < leftCol.size(); i++) {    
        similarityScore += leftCol[i] * rightOccurs[leftCol[i]];
    }    
    cout << similarityScore << endl;

    return 0;
}