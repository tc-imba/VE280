//
// Created by liu on 27/7/2020.
//

#include <iostream>
#include <sstream>
#include <cstring>

#include "dlist.h"

using namespace std;

struct CacheBlock {
    size_t index;
    int value;
};

int main() {
    size_t cacheSize, memorySize;
    cin >> cacheSize >> memorySize >> ws;

    auto memory = new int[memorySize];
    memset(memory, 0, memorySize * sizeof(int));

    Dlist<CacheBlock> cache;
    size_t cacheUsed = 0;

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
            auto block = new CacheBlock{index, value};
            auto victim = cache.remove([](const CacheBlock *a, const CacheBlock *b) { return a->index == b->index; },
                                       block);
            if (victim) {
                if (read) block->value = victim->value;
                cache.insertFront(block);
                delete victim;
            } else {
                if (read) block->value = memory[index];
                cache.insertFront(block);
                cacheUsed++;
                if (cacheUsed > cacheSize) {
                    victim = cache.removeBack();
                    cacheUsed--;
                    memory[victim->index] = victim->value;
                    delete victim;
                }
            }
            if (read) {
                cout << block->value << endl;
            }
        } else if (instruction == "PRINTCACHE") {
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            auto temp = cache;
            while (!temp.isEmpty()) {
                auto block = temp.removeFront();
                cout << block->index << " " << block->value << endl;
                delete block;
            }
        } else if (instruction == "PRINTMEM") {
            if (!iss.eof()) {
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            for (int i = 0; i < memorySize; i++) {
                cout << memory[i] << " ";
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
