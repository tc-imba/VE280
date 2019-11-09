//
// Created by liu on 19-7-12.
//

#include <iostream>
#include <cassert>
#include "player.h"
#include "quarto.h"

class HumanPlayer : public Player {
public:
    HumanPlayer() noexcept : Player(nullptr, nullptr) {}

    void initialize(Board *b, Pool *p) {
        if (!this->board) {
            this->board = b;
            this->pool = p;
        }
    }

    Piece &selectPiece() override {
        while (true) {
            try {
                std::cout << "Enter a piece:";
                std::string str;
                std::cin >> str;
                return pool->getUnusedPiece(str);
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    Square &selectSquare(const Piece &p) override {
        while (true) {
            try {
                std::cout << "Enter a position:";
                std::string str;
                std::cin >> str;
                return board->getEmptySquare(str);
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
};


class MyopicPlayer : public Player {
private:
    struct Pieces {
        Piece *pieces[NP] = {};
        int size = 0;

        Pieces() = default;

        explicit Pieces(const MyopicPlayer *player) {
            for (auto h:{SHORT, TALL}) {
                for (auto c:{BEIGE, SEPIA}) {
                    for (auto s:{CIRCLE, SQUARE}) {
                        for (auto t:{HOLLOW, SOLID}) {
                            try {
                                auto &piece = player->pool->getUnusedPiece(h, c, s, t);
                                this->addPiece(piece);
                            } catch (const std::exception &e) {}
                        }
                    }
                }
            }
        }

        void addPiece(Piece &piece) {
            this->pieces[this->size++] = &piece;
        }
    };

    struct Squares {
        Square *squares[NP] = {};
        int size = 0;

        Squares() = default;

        explicit Squares(MyopicPlayer *player) {
            for (auto v:{A, B, C, D}) {
                for (auto h:{H1, H2, H3, H4}) {
                    try {
                        auto &square = player->board->getEmptySquare(v, h);
                        this->addSquare(square);
                    } catch (const std::exception &e) {}
                }
            }
        }

        void addSquare(Square &square) {
            this->squares[this->size++] = &square;
        }
    };


    bool isBadPiece(const Piece &piece, Squares &availableSquares) {
        for (int i = 0; i < availableSquares.size; i++) {
            if (this->board->isWinning(piece, *availableSquares.squares[i])) {
                return true;
            }
        }
        return false;
    }

public:
    MyopicPlayer() noexcept : Player(nullptr, nullptr) {}

    void initialize(Board *b, Pool *p, unsigned int seed) {
        if (!this->board) {
            this->board = b;
            this->pool = p;
            srand(seed);
        }
    }

    Piece &selectPiece() override {
        Squares availableSquares(this);
        Pieces availablePieces(this);
        Pieces badPieces, notBadPieces;
        for (int i = 0; i < availablePieces.size; i++) {
            auto &piece = *availablePieces.pieces[i];
            if (isBadPiece(piece, availableSquares)) {
                badPieces.addPiece(piece);
            } else {
                notBadPieces.addPiece(piece);
            }
        }
        if (notBadPieces.size > 0) {
            return *notBadPieces.pieces[rand() % notBadPieces.size];
        }
        assert(badPieces.size > 0);
        return *badPieces.pieces[rand() % badPieces.size];
    }

    Square &selectSquare(const Piece &p) override {
        Squares availableSquares(this);
        Squares notWinningSquares;
        for (int i = 0; i < availableSquares.size; i++) {
            auto &square = *availableSquares.squares[i];
            if (this->board->isWinning(p, square)) {
                return square;
            }
            notWinningSquares.addSquare(square);
        }
        assert(notWinningSquares.size > 0);
        return *notWinningSquares.squares[rand() % notWinningSquares.size];
    }
};

static HumanPlayer humanPlayer;
static MyopicPlayer myopicPlayer;

Player *getHumanPlayer(Board *b, Pool *p) {
    humanPlayer.initialize(b, p);
    return &humanPlayer;
}

Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s) {
    myopicPlayer.initialize(b, p, s);
    return &myopicPlayer;
}
