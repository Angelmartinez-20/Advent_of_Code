#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
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

void harddrive_map(const vector<pair<int, int>> &pairedFiles, vector<int> &harddrive, unordered_map<int, int> &file_dict, int &largest_id) {
    int idVal = 0;

    for (int i = 0; i < pairedFiles.size(); i++) {
        harddrive.insert(harddrive.end(), pairedFiles[i].first, idVal);
        harddrive.insert(harddrive.end(), pairedFiles[i].second, -1);
        file_dict[idVal] = pairedFiles[i].first;
        idVal++;
    }

    largest_id = idVal - 1;
}

int num_consecutive_space(const vector<int>& harddrive, int itr) {
    int consecutive_count = 0;
    for (size_t i = itr; i < harddrive.size(); i++) {
        if (harddrive[i] != -1) break;
        consecutive_count++;
    }
    return consecutive_count;
}

void optimize_space(vector<int> &harddrive, const unordered_map<int, int> &fileDict, int largestID) {
    int descID = largestID;

    while (descID > 0) {
        size_t i = 0;
        while (i < harddrive.size()) {
            if (harddrive[i] == descID) break;
            if (harddrive[i] == -1) {
                int num_space = num_consecutive_space(harddrive, i);
                if (num_space < fileDict.at(descID)) {
                    i++;
                    continue;
                } else {
                    size_t valLoc = find(harddrive.begin(), harddrive.end(), descID) - harddrive.begin();
                    for (int idx = 0; idx < fileDict.at(descID); idx++)
                        swap(harddrive[i + idx], harddrive[valLoc + idx]);
                    break;
                }
            }
            i++;
        }
        descID--;
    }
}

long long calculate_checksum(vector<int> &optHarddrive) {
    long long checksum = 0;
    for (size_t idx = 0; idx < optHarddrive.size(); ++idx) {
        if (optHarddrive[idx] == -1) checksum += idx * 0;
        else checksum += idx * optHarddrive[idx];
    }
    return checksum;
}



int main() {
    vector<int> data = read_file();
    vector<pair<int, int>> pairedFiles = make_pairs(data);

    vector<int> harddrive;
    unordered_map<int, int> fileDict;
    int largestID;
    harddrive_map(pairedFiles, harddrive, fileDict, largestID);
    optimize_space(harddrive, fileDict, largestID);

    long long checksum = calculate_checksum(harddrive);
    cout << checksum << endl;
    return 0;
}