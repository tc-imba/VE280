//
// Created by liu on 19-7-11.
//

#include <functional>

#include "board.h"
#include "exceptions.h"

Board::Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->grid[i][j] = Square(Vaxis(i), Haxis(j));
        }
    }
}

Square &Board::getSquare(Vaxis v, Haxis h) {
    return this->grid[v][h];
}

Square &Board::getEmptySquare(Vaxis v, Haxis h) {
    auto &square = this->getSquare(v, h);
    if (!square.isEmpty()) {
        throw SquareException(square, "not empty");
    }
    return square;
}

Square &Board::getEmptySquare(const std::string &s) {
    if (s.length() != 2) {
        throw InvalidInputException(s);
    }
    int v = s[0] - 'A';
    int h = s[1] - '1';
    if (v < 0 || v >= 4 || h < 0 || h >= 4) {
        throw InvalidInputException(s);
    }
    return getEmptySquare(Vaxis(v), Haxis(h));
}

void Board::place(Piece &p, Square &sq) {
    sq.setPiece(&p);
    p.setUsed(true);
}

typedef bool (Piece::*PieceComparator)(const Piece &) const;

const static PieceComparator pieceComparators[] = {
        &Piece::compareHeight,
        &Piece::compareColor,
        &Piece::compareShape,
        &Piece::compareTop,
};

static bool
haveSameAttr(const PieceComparator &comp, const Piece &piece, const Square &square1, const Square &square2) {
    if (square1.getV() == square2.getV() && square1.getH() == square2.getH()) return true;
    return ((piece).*(comp))(square2.getPiece());
}

template<typename... Args>
static bool haveSameAttr(const PieceComparator &comp, const Piece &piece, const Square &square1,
                         const Square &square2, Args... args) {
    return haveSameAttr(comp, piece, square1, square2) && haveSameAttr(comp, piece, square1, args...);
}

template<typename ...Args>
static bool haveSame(const Piece &piece, const Square &square, Args... args) {
    try {
        for (int i = 0; i < 4; i++) {
            if (haveSameAttr(pieceComparators[i], piece, square, args...)) {
                return true;
            }
        }
    } catch (const SquareException &e) {
        return false;
    }
    return false;
}

bool Board::isWinning(const Piece &p, const Square &sq) {
    auto v = sq.getV();
    auto h = sq.getH();
    return haveSame(p, sq, this->grid[v][0], this->grid[v][1], this->grid[v][2], this->grid[v][3]) ||
           haveSame(p, sq, this->grid[0][h], this->grid[1][h], this->grid[2][h], this->grid[3][h]) ||
           (sq.isOnFirstDiagonal() &&
            haveSame(p, sq, this->grid[0][0], this->grid[1][1], this->grid[2][2], this->grid[3][3])) ||
           (sq.isOnSecondDiagonal() &&
            haveSame(p, sq, this->grid[0][3], this->grid[1][2], this->grid[2][1], this->grid[3][0]));
}

std::string Board::toString() const {
    std::string str("     1    2    3    4\n");
    for (int i = 0; i < 4; i++) {
        str += "   +----+----+----+----+\n";
        std::string str1, str2;
        str1 += " ";
        str1 += (char) ('a' + i);
        str1 += " | ";
        str2 += "   | ";
        for (int j = 0; j < 4; j++) {
            auto &square = grid[i][j];
            if (square.isEmpty()) {
                str1 += "   | ";
                str2 += "   | ";
            } else {
                auto temp = square.getPiece().toString();
                str1 += temp.substr(0, 2);
                str1 += " | ";
                str2 += temp.substr(2, 2);
                str2 += " | ";
            }
        }
        str += str1;
        str += '\n';
        str += str2;
        str += '\n';
    }
    str += "   +----+----+----+----+\n";
    return str;
}






