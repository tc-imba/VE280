//
// Created by liu on 16-7-4.
//

#include "deck.h"

template<class T>
static inline int length(T &a) {
    return sizeof(a) / sizeof(a[0]);
}

template<class T>
static inline T operator++(T &a, int) {
    auto old = a;
    a = T(a + 1);
    return old;
}

Deck::Deck() {
    this->reset();
}

void Deck::reset() {
    for (auto suit = SPADES; suit < length(SuitNames); suit++) {
        for (auto spot = TWO; spot < length(SpotNames); spot++) {
            int index = suit * length(SpotNames) + spot;
            this->deck[index].suit = suit;
            this->deck[index].spot = spot;
        }
    }
    this->next = 0;
}

void Deck::shuffle(int n) {
    int leftNum = n, rightNum = DeckSize - n;
    Card leftCards[leftNum + 1], rightCards[rightNum + 1];
    for (int i = 0; i < leftNum; i++) {
        leftCards[i] = this->deck[i];
    }
    for (int i = 0; i < rightNum; i++) {
        rightCards[i] = this->deck[leftNum + i];
    }
    int left = 0, right = 0;
    while (left < leftNum || right < rightNum) {
        if (right < rightNum) {
            this->deck[left + right] = rightCards[right];
            ++right;
        }
        if (left < leftNum) {
            this->deck[left + right] = leftCards[left];
            ++left;
        }
    }
    this->next = 0;
}

Card Deck::deal() {
    if (this->next < DeckSize) {
        return this->deck[this->next++];
    }
    throw DeckEmpty();
}

int Deck::cardsLeft() {
    return DeckSize - this->next;
}