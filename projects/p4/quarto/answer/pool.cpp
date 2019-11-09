//
// Created by liu on 19-7-11.
//

#include "pool.h"
#include "exceptions.h"

Piece &Pool::getUnusedPiece(int index) {
    auto &piece = this->pieces[index];
    if (piece.isUsed()) {
        throw UsedPieceException(piece);
    }
    return piece;
}

Pool::Pool() {
    for (size_t i = 0; i < NP; i++) {
        auto h = Height(i >> 3u);
        auto c = Color((i % 8) >> 2u);
        auto s = Shape((i % 4) >> 1u);
        auto t = Top(i % 2);
        this->pieces[i] = Piece(h, c, s, t);
    }
}

Piece &Pool::getUnusedPiece(Height h, Color c, Shape s, Top t) {
    return this->getUnusedPiece(h * 8 + c * 4 + s * 2 + t);
}

Piece &Pool::getUnusedPiece(const std::string &in) {
    size_t index = 0;
    if (in.length() != 4) {
        throw InvalidInputException(in);
    }
    for (int i = 0; i < 4; i++) {
        if (in[i] == ALLCODE[i][1]) {
            index += 1;
        } else if (in[i] != ALLCODE[i][0]) {
            throw InvalidInputException(in);
        }
        index <<= 1u;
    }
    index >>= 1u;
    return this->getUnusedPiece(index);
}

std::string Pool::toString() const {
    std::string str1("Available:\n"), str2("\n");
    bool flag = false;
    for (int i = 0; i < NP; i++) {
        auto &piece = this->pieces[i];
        if (!piece.isUsed()) {
            flag = true;
            auto temp = this->pieces[i].toString();
            str1 += temp.substr(0, 2);
            str1 += ' ';
            str2 += temp.substr(2, 2);
            str2 += ' ';
        }
    }
    if (!flag) {
        return "";
    }
    return str1 += (str2 += '\n');
}
