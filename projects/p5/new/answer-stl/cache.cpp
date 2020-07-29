//
// Created by liu on 27/7/2020.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

int main() {
    size_t cacheSize, memorySize;
    cin >> cacheSize >> memorySize >> ws;

    vector<int> memory(memorySize);
    list<pair<size_t, int>> cache;
    unordered_map<size_t, list<pair<size_t, int>>::iterator> hashtable;

    string line;
    istringstream iss;
    while (getline(cin, line)) {
        iss.clear();
        iss.str(line);

        string instruction;
        iss >> instruction >> ws;

        if (instruction == "READ" || instruction == "WRITE") {
            size_t index;
            int value;
            bool read = instruction == "READ";
            if (!(iss >> index >> ws)) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if (index >= memorySize) {
                cout << "ERROR: Address out of bound" << endl;
                continue;
            }
            if (!read && !(iss >> value >> ws)) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            auto it = hashtable.find(index);
            if (it != hashtable.end()) {
                if (read) value = it->second->second;
                cache.erase(it->second);
                cache.emplace_front(index, value);
                it->second = cache.begin();
            } else {
                if (read) value = memory[index];
                cache.emplace_front(index, value);
                hashtable.emplace_hint(it, index, cache.begin());
                if (cache.size() > cacheSize) {
                    it = hashtable.find(cache.back().first);
                    if (it != hashtable.end()) {
                        hashtable.erase(it);
                    }
                    memory[cache.back().first] = cache.back().second;
                    cache.pop_back();
                }
            }
            if (read) {
                cout << value << endl;
            }
        } else if (instruction == "PRINTCACHE") {
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            for (auto &item : cache) {
                cout << item.first << " " << item.second << endl;
            }
        } else if (instruction == "PRINTMEM") {
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            for (auto &item : memory) {
                cout << item << " ";
            }
            cout << endl;
        } else if (instruction == "EXIT") {
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            break;
        } else {
            cout << "ERROR: Unknown instruction" << endl;
        }

    }


    return 0;
}
