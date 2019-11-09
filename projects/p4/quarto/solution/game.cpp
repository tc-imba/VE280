//
// Created by liu on 19-7-11.
//

#include <iostream>

#include "board.h"
#include "player.h"

using namespace std;

Player *getPlayer(Board *b, Pool *p, const char *type, unsigned int seed) {
    if (type[0] == 'h') {
        return getHumanPlayer(b, p);
    }
    return getMyopicPlayer(b, p, seed);
}


int main(int argc, char *argv[]) {
    Board board;
    Pool pool;
    unsigned int seed = argc >= 4 ? strtoul(argv[3], nullptr, 10) : 0;
    Player *players[2] = {
            getPlayer(&board, &pool, argv[1], seed),
            getPlayer(&board, &pool, argv[2], seed)
    };

    cout << board.toString() << endl;
    cout << pool.toString() << endl;

    for (int n = 0; n < NP; n++) {
        int i = n % 2;
        int j = 1 - i;

        cout << "Player " << i + 1 << "'s turn to select a piece:" << endl;
        auto &piece = players[i]->selectPiece();
        cout << piece.toString() << " selected." << endl << endl;

        cout << "Player " << j + 1 << "'s turn to select a square:" << endl;
        auto &square = players[j]->selectSquare(piece);
        cout << square.toString() << " selected." << endl << endl;

        board.place(piece, square);
        cout << board.toString() << endl;
        cout << pool.toString() << endl;

        if (board.isWinning(piece, square)) {
            cout << "Player " << j + 1 << " has won!" << endl;
            return 0;
        }
    }
    cout << "It is a draw." << endl;
    return 0;
}