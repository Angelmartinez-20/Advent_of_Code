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
        // checks if entire row either increminting or decrementing
        if ((isIncrem && row[i] < row[i-1]) || (!isIncrem && row[i] > row[i-1]))
            return false;
    }
    return true;
}

int main() {
    vector<vector<int>> data;
    readData(data);
    int numSaves = 0;

    for(int i = 0; i < data.size(); i++) {
        if (isSafe(data[i])) numSaves++;
    }

    cout << numSaves << endl;
    return 0;
}