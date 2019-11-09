//
// Created by liu on 19-7-11.
//

#include "square.h"
#include "exceptions.h"

Square::Square(Vaxis v, Haxis h) : v(v), h(h), p(nullptr) {}

Vaxis Square::getV() const {
    return this->v;
}

void Square::setV(Vaxis v) {
    this->v = v;
}

Haxis Square::getH() const {
    return this->h;
}

void Square::setH(Haxis h) {
    this->h = h;
}

const Piece &Square::getPiece() const {
    if (!this->p) {
        throw SquareException(*this, "empty");
    }
    return *this->p;
}

void Square::setPiece(const Piece *p) {
    this->p = p;
}

bool Square::isEmpty() const {
    return p == nullptr;
}

bool Square::isOnFirstDiagonal() const {
    return (int) (this->v) == (int) (this->h);
}

bool Square::isOnSecondDiagonal() const {
    return this->v + this->h == 3;
}

std::string Square::toString() const {
    std::string str;
    str += (char) ('A' + this->v);
    str += (char) ('1' + this->h);
    return str;
}
