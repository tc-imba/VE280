//
// Created by liu on 19-7-11.
//

#include "piece.h"

Piece::Piece(Height h, Color c, Shape s, Top t) : h(h), c(c), s(s), t(t), used(false) {}

bool Piece::compareHeight(const Piece &p) const {
    return this->h == p.h;
}

bool Piece::compareColor(const Piece &p) const {
    return this->c == p.c;
}

bool Piece::compareShape(const Piece &p) const {
    return this->s == p.s;
}

bool Piece::compareTop(const Piece &p) const {
    return this->t == p.t;
}

bool Piece::isUsed() const {
    return this->used;
}

void Piece::setUsed(bool u) {
    this->used = u;
}

std::string Piece::toString() const {
    std::string str;
    str += HCODE[this->h];
    str += CCODE[this->c];
    str += SCODE[this->s];
    str += TCODE[this->t];
    return str;
}

