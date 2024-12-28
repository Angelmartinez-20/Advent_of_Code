#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<int> read_file() {
    ifstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error Opening File" << endl;
        exit(-1);
    }

    string line;
    vector<int> data;
    while(getline(file, line)) {
        for (char ch : line)
            data.push_back(ch - '0');  // char to int
    }

    if (data.size() % 2 != 0) data.push_back(0);
    file.close();
    return data;
}

vector<pair<int, int>> make_pairs(vector<int> &data) {
    vector<pair<int, int>> pairedFiles;

    for (size_t i = 0; i < data.size(); i += 2) {
        pairedFiles.push_back({data[i], data[i + 1]});
    }

    return pairedFiles;
}

vector<int> harddrive_map(vector<pair<int, int>> &pairedFiles) {
    vector<int> harddrive;
    int idVal = 0;

    for (int i = 0; i < pairedFiles.size(); i++) {
        harddrive.insert(harddrive.end(), pairedFiles[i].first, idVal);
        harddrive.insert(harddrive.end(), pairedFiles[i].second, -1);
        idVal++;
    }

    return harddrive;
}

vector<int> optimize_space(vector<int> &harddrive) {
    vector<int> optHarddrive;
    int leftPtr = 0;
    int rightPtr = harddrive.size()-1;

    while (leftPtr <= rightPtr) {
        if (harddrive[leftPtr] != -1)
            optHarddrive.push_back(harddrive[leftPtr]);
        else {
            while (harddrive[rightPtr] == -1)
                rightPtr -= 1;
            if (leftPtr < rightPtr)
                optHarddrive.push_back(harddrive[rightPtr]);
            rightPtr--;
        }
        leftPtr++;
    }
        
    return optHarddrive;
}

long long calculate_checksum(vector<int> &optHarddrive) {
    long long checksum = 0;
    for (int i = 0; i < optHarddrive.size(); i++) {
        checksum += (i * optHarddrive[i]);
    }
    return checksum;
}



int main() {
    vector<int> data = read_file();
    vector<pair<int, int>> pairedFiles = make_pairs(data);
    vector<int> harddrive = harddrive_map(pairedFiles);
    vector<int> optHarddrive = optimize_space(harddrive);
    long long checksum = calculate_checksum(optHarddrive);
    cout << checksum << endl;
    return 0;
}