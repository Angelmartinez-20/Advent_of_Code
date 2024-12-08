#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
using namespace std;

void readFile(string &memoryData) {
    ifstream file("test.txt");
    if (!file.is_open()){
        cerr << "Error Opening File" << endl;
        exit(-1);
    }

    char ch;
    while (file.get(ch)) memoryData += ch;
    file.close();
}

int countPattern(string &memoryData, regex pattern) {
    vector<pair<int, int>> matches;

    // finds matches
    sregex_iterator begin(memoryData.begin(), memoryData.end(), pattern);
    sregex_iterator end;    

    // collects matches
    for (sregex_iterator it = begin; it != end; it++) {
        int num1 = stoi((*it)[1].str());
        int num2 = stoi((*it)[2].str());
        matches.push_back({num1, num2});
    }

    int numOccur = 0;
    for (vector<pair<int, int>>::iterator it = matches.begin(); it != matches.end(); it++) {
        numOccur += it->first * it->second;
    }
    return numOccur;
}

int main() {
    string memoryData;
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    int numOccur = 0;

    readFile(memoryData);
    numOccur = countPattern(memoryData, pattern);

    cout << numOccur << endl;
    return 0;
}