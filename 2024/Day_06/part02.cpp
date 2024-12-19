#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void read_file(vector<vector<char>> &data) {
    ifstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error Opening File" << endl;
        exit(-1);       
    }

    string line;
    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }
    file.close();
}

// find location of '^'
pair<int, int> init_loc(const vector<vector<char>>& data) {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == '^') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// find marching path and returns num distinct positions
int find_path(int i, int j, vector<vector<char>> data) {
    int dir_pos = 0;
    vector<int> dir = {1, 2, 3, 4};  // [up, right, down, left]
    int steps = 0;

    while (true) {
        // Going up
        if (dir_pos % dir.size() == 0) {
            for (int idx = i; idx >= 0; idx--) {
                steps += 1;
                i = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                } else if (data[i][j] == '#') {
                    i++;  // Go back 1
                    break;
                }
            }
            if (i == 0) return 0;
        }
        // Going right
        else if (dir_pos % dir.size() == 1) {
            for (int idx = j; idx < data[i].size(); idx++) {
                steps += 1;
                j = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                } else if (data[i][j] == '#') {
                    j--;  // Go back 1
                    break;
                }
            }
            if (j == data[i].size() - 1) return 0;
        }
        // Going down
        else if (dir_pos % dir.size() == 2) {
            for (int idx = i; idx < data.size(); idx++) {
                steps += 1;
                i = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                } else if (data[i][j] == '#') {
                    i--;  // Go back 1
                    break;
                }
            }
            if (i == data.size() - 1) return 0;
        }
        // Going left
        else {
            for (int idx = j; idx >= 0; idx--) {
                steps += 1;
                j = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                } else if (data[i][j] == '#') {
                    j++;  // Go back 1
                    break;
                }
            }
            if (j == 0) return 0;
        }
        dir_pos++;
        if (steps > 10000) return 1;    // I should use a better cycling detect algo
    }
}

int main() {
    vector<vector<char>> data;
    read_file(data);
    auto [i, j] = init_loc(data);
    int num_obsticles = 0;

    for(int idx = 0; idx < data.size(); idx++) {
        for(int jdx = 0; jdx < data.size(); jdx++) {
            if (data[idx][jdx] == '.') {
                data[idx][jdx] = '#';
                num_obsticles += find_path(i, j, data);
                data[idx][jdx] = '.';
            }
        }
    }
    cout << num_obsticles << endl;

    return 0;
}