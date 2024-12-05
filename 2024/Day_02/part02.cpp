#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void readData(vector<vector<int>> &data) {
    ifstream file("test.txt");
    if (!file.is_open()){
        cerr << "Error Opening File" << endl;
        exit(-1);
    }

    string line;
    while(getline(file, line)) {
        istringstream ss(line);
        int val;
        vector<int> row;
        while (ss >> val) row.push_back(val);
        data.push_back(row);
    }
}

bool isSafe(vector<int> row) {
    bool isIncrem = row[0] < row[1];
    for (int i = 1; i < row.size(); i++) {
        int dist = abs(row[i] - row[i-1]);
        if (dist < 1 || dist > 3) return false;
        if ((isIncrem && row[i] < row[i-1]) || (!isIncrem && row[i] > row[i-1]))
            return false;
    }
    return true;
}

int main() {
    vector<vector<int>> data;
    readData(data);
    int numSaves = 0;

    // checks each row id safe or not
    for(int i = 0; i < data.size(); i++) {
        // checks if row is safe if remove ith elemnent
        for(int j = 0; j < data[i].size(); j++) {
            vector<int> newRow = data[i];
            newRow.erase(newRow.begin()+j);
            if (isSafe(newRow)) {
                numSaves++; 
                break;
            }
        }
    }

    cout << numSaves << endl;
    return 0;
}