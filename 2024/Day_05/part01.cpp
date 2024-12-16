#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm> 

using namespace std;

void readFile(unordered_map<int, vector<int>> &rules, vector<vector<int>> &updates) {
    // opens file
    ifstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        exit(-1);
    }

    // read entire file
    stringstream ss;
    ss << file.rdbuf();
    string data = ss.str();
    file.close();

    // split data into sections
    size_t first_split = data.find("\n\n");
    string first_section = data.substr(0, first_split);
    string second_section = data.substr(first_split + 2);

    // process first section
    istringstream first_stream(first_section);
    string line;
    while (getline(first_stream, line)) {
        size_t delimiter_pos = line.find('|');
        int left = stoi(line.substr(0, delimiter_pos));
        int right = stoi(line.substr(delimiter_pos + 1));

        // Add left to the right in the rules map
        if (rules.find(right) == rules.end()) {
            rules[right] = std::vector<int>();
        }
        rules[right].push_back(left);
    }

    // Process the second section
    istringstream second_stream(second_section);
    while (getline(second_stream, line)) {
        vector<int> row;
        istringstream row_stream(line);
        string num_str;
        while (std::getline(row_stream, num_str, ',')) {
            row.push_back(std::stoi(num_str));
        }
        updates.push_back(row);
    }
}

int right_order(const vector<int>& row, const unordered_map<int, vector<int>>& rules) {
    for (int i = 0; i < row.size() - 1; i++) {
        for (int j = i + 1; j < row.size(); j++) {
            // if row[i] in rules and row[j] in rules[row[i]]
            if (rules.find(row[i]) != rules.end() &&
                find(rules.at(row[i]).begin(), rules.at(row[i]).end(), row[j]) != rules.at(row[i]).end()) {
                return 0;
            }
        }
    }
    return row[row.size() / 2];
}

int main() {
    unordered_map<int, vector<int>> rules;
    vector<vector<int>> updates;
    int middleSum = 0;

    readFile(rules, updates);

    for (int i = 0; i < updates.size(); i++) {
        middleSum += right_order(updates[i], rules);  
    }

    cout << middleSum << endl;

    return 0;
}
