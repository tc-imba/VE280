//
// Created by liu on 16-7-4.
//

#include "hand.h"

Hand::Hand() {
    this->discardAll();
}

void Hand::discardAll() {
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c) {
    switch (c.spot) {
        case ACE:
            if (this->curValue.soft || this->curValue.count >= 21) {
                this->curValue.count++;
            } else {
                this->curValue.count += 11;
                this->curValue.soft = true;
            }
            break;
        case JACK:
        case QUEEN:
        case KING:
            this->curValue.count += 10;
            break;
        default:
            this->curValue.count += (c.spot + 2);
            break;
    }
    if (this->curValue.soft && this->curValue.count > 21) {
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
}

HandValue Hand::handValue() const {
    return this->curValue;
}