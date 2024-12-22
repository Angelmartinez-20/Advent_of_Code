#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

const vector<string> OPERATORS = {"+", "*", "||"};

// reads data into vector of pairs 
void read_file(vector<pair<long long, vector<long long>>> &data) {
    ifstream file("test.txt");
    string line;

    while(getline(file, line)) {
        stringstream ss(line);
        string left, right;
        getline(ss, left, ':');
        getline(ss, right);
        
        long long target = stoll(left); 
        vector<long long> numbers;

        stringstream numStream(right);
        string num;
        while (numStream >> num) {
            numbers.push_back(stoll(num)); 
        }
        
        data.push_back({target, numbers});
    }
}

// evaluates expression left to right
bool evaluate(const pair<long long, vector<long long>> &problem, const vector<string> &operators) {
    long long target = problem.first;
    const vector<long long> &numbers = problem.second;
    long long result = numbers[0];
    
    // applies combination of operators to results
    for (size_t i = 1; i < numbers.size(); i++) {
        if (operators[i-1] == "+") {
            result += numbers[i];
        } else if (operators[i-1] == "*") {
            result *= numbers[i];
        } else if (operators[i-1] == "||") {
            result = stoll(to_string(result) + to_string(numbers[i]));
        }
    }
    
    return result == target;
}

// generates all combinations of operators
void generate_combinations(vector<string> &combination, size_t num_operators, bool &found, const pair<long long, vector<long long>> &problem) {
    if (combination.size() == num_operators) {
        if (evaluate(problem, combination)) {
            found = true;
        }
        return;
    }
    
    // generates all combinations of the operators
    for (const string &op : OPERATORS) {
        combination.push_back(op);
        generate_combinations(combination, num_operators, found, problem);
        if (found) return;
        combination.pop_back();
    }
}

// generate and checks each combinations
bool checkEquation(const pair<long long, vector<long long>> &problem) {
    size_t num_operators = problem.second.size() - 1;

    vector<string> combination;
    bool found = false;
    generate_combinations(combination, num_operators, found, problem);
    
    return found;
}

int main() {
    vector<pair<long long, vector<long long>>> data;
    read_file(data);

    long long totalSum = 0;
    for (const auto &problem : data) {
        if (checkEquation(problem))
            totalSum += problem.first;
    }
    cout << totalSum << endl;

    return 0;
}
