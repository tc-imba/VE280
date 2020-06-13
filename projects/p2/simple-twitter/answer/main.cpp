#include "simulation.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
#ifdef DEBUG
    std::ofstream fout("test.out1");
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(fout.rdbuf());
#endif
    try {
        if (argc <= 2) {
            throw InvalidArgumentException();
        }
        auto &server = Server::getInstance();
        server.initUsers(argv[1]);
        server.readLog(argv[2]);
    } catch (SimpleTwitterException &e) {
        std::cout << e.what() << std::endl;
    }
#ifdef DEBUG
    std::cout.rdbuf(coutBuf);
    fout.close();
#endif
    return 0;
}
