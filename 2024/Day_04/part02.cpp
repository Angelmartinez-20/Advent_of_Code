#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

const vector<vector<int>> first_diag = {{-1,-1}, {1,1}};    // upper left, lower right 
const vector<vector<int>> second_diag = {{1,-1},{-1,1}};    // lower left, upper right 
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

bool find_mas(int i, int j, vector<vector<char>> &data, const vector<vector<int>> diag) {
    int next_i = i+diag[0][0];
    int next_j = j+diag[0][1];

    // check if in bounds
    if ((next_i >= 0 && next_i < data.size()) && (next_j >= 0 && next_j < data.size())){
        if(data[next_i][next_j] == 'M'){
            next_i = i+diag[1][0];
            next_j = j+diag[1][1];
            // check if in bounds
            if((next_i >= 0 && next_i < data.size()) && (next_j >= 0 && next_j < data.size())){
                if(data[next_i][next_j] == 'S') 
                    return true;
                else return false;
            }
            else return false;
        } else if (data[next_i][next_j] == 'S') {
            next_i = i+diag[1][0];
            next_j = j+diag[1][1];
            // check if in bounds
            if ((next_i >= 0 && next_i < data.size()) && (next_j >= 0 && next_j < data.size())){
                if(data[next_i][next_j] == 'M')
                    return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }
    return false;  

}
// compares each possible directions
void find_x(int i, int j, vector<vector<char>> &data) {
    if(find_mas(i, j, data, first_diag) && find_mas(i, j, data, second_diag)) {
        num_finds++;
    }
}

int main() {
    vector<vector<char>> data;
    readData(data);

    // iters through data looking for "X"
    for(int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == 'A') find_x(i, j, data);
        }
    }

    cout << num_finds << endl;
    return 0;
}