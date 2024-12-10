#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// 8 possible search locations
const vector<vector<int>> possible_dir = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
const string xmas = "XMAS";
int num_finds = 0;


void readData(vector<vector<char>> &data) { 
    ifstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error Opening File!" << endl;
        exit(-1);
    }

    string line;
    while(getline(file, line)) {
        vector<char> lineData(line.begin(), line.end());
        data.push_back(lineData);
    }
    file.close();
}

void compare_word(int i, int j, vector<int> dir, vector<vector<char>> &data) {
    for(int itr = 1; itr < xmas.size(); itr++) {
        int next_i = i + itr * dir[0];
        int next_j = j + itr * dir[1];
        // check if position no out of bounds or !match word
        if ((next_i < 0 || next_i >= data.size()) ||
            (next_j < 0 || next_j >= data[next_i].size()) ||
            data[next_i][next_j] != xmas[itr])
            return;       
    }
    num_finds += 1;
}

// compares each possible directions
void find_word(int i, int j, vector<vector<char>> &data) {
    for(int itr = 0; itr < possible_dir.size(); itr++) {
        compare_word(i, j, possible_dir[itr], data);
    }
}

int main() {
    vector<vector<char>> data;
    readData(data);

    // iters through data looking for "X"
    for(int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == xmas[0]) find_word(i, j, data);
        }
    }

    cout << num_finds << endl;
    return 0;
}