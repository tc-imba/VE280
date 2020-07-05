//
// Created by liu on 16-7-4.
//

#include "player.h"

static bool playerDraw(Card dealer, const Hand &player) {
    auto value = player.handValue();
    if (value.soft) {
        return (value.count <= 17) ||
               (value.count == 18 && !(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT));
        /*if (value.count <= 17) {
            return true;
        } else if (value.count == 18 && !(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT)) {
            return true;
        }*/
    } else {
        return (value.count <= 11) ||
               (value.count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX)) ||
               (value.count >= 13 && value.count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX));
        /*if (value.count <= 11) {
            return true;
        } else if (value.count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX)) {
            return true;
        } else if (value.count >= 13 && value.count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX)) {
            return true;
        }*/
    }
//        return false;
}

class SimplePlayer : public Player {
public:

    int bet(unsigned int bankroll, unsigned int minimum) override {
        return (int) minimum;
    }

    bool draw(Card dealer, const Hand &player) override {
        return playerDraw(dealer, player);
    }

    void expose(Card c) override {}

    void shuffled() override {}

};

Player *get_Simple() {
    return (Player *) new SimplePlayer();
}

class CountingPlayer : public Player {
private:
    int count = 0;
public:
    CountingPlayer() = default;

    int bet(unsigned int bankroll, unsigned int minimum) override {
        if (count >= 2 && minimum * 2 <= bankroll) {
            return (int) minimum * 2;
        }
        return (int) minimum;
    }

    bool draw(Card dealer, const Hand &player) override {
        return playerDraw(dealer, player);
    }

    void expose(Card c) override {
        if (c.spot >= TEN) {
            count--;
        } else if (c.spot >= TWO && c.spot <= SIX) {
            count++;
        }
    }

    void shuffled() override {
        this->count = 0;
    }
};

Player *get_Counting() {
    return (Player *) new CountingPlayer();
}