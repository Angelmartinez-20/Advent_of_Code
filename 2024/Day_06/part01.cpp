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
int find_path(int i, int j, vector<vector<char>>& data) {
    int distinct_pos = 0;
    int dir_pos = 0;
    vector<int> dir = {1, 2, 3, 4};  // [up, right, down, left]

    while (true) {
        // Going up
        if (dir_pos % dir.size() == 0) {
            for (int idx = i; idx >= 0; idx--) {
                i = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                    distinct_pos++;
                } else if (data[i][j] == '#') {
                    i++;  // Go back 1
                    break;
                }
            }
            if (i == 0) return distinct_pos;
        }
        // Going right
        else if (dir_pos % dir.size() == 1) {
            for (int idx = j; idx < data[i].size(); idx++) {
                j = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                    distinct_pos++;
                } else if (data[i][j] == '#') {
                    j--;  // Go back 1
                    break;
                }
            }
            if (j == data[i].size() - 1) return distinct_pos;
        }
        // Going down
        else if (dir_pos % dir.size() == 2) {
            for (int idx = i; idx < data.size(); idx++) {
                i = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                    distinct_pos++;
                } else if (data[i][j] == '#') {
                    i--;  // Go back 1
                    break;
                }
            }
            if (i == data.size() - 1) return distinct_pos;
        }
        // Going left
        else {
            for (int idx = j; idx >= 0; idx--) {
                j = idx;
                if (data[i][j] == '.') {
                    data[i][j] = 'X';
                    distinct_pos++;
                } else if (data[i][j] == '#') {
                    j++;  // Go back 1
                    break;
                }
            }
            if (j == 0) return distinct_pos;
        }
        dir_pos++;
    }
}

int main() {
    vector<vector<char>> data;
    read_file(data);
    auto [i, j] = init_loc(data);
    int distinct_pos = find_path(i, j, data);
    cout << distinct_pos + 1 << endl;

    return 0;
}
