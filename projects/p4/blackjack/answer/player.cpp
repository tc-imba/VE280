//
// Created by liu on 16-7-4.
//

#include "player.h"

class SimplePlayer : public Player
{
public:

    int bet(unsigned int bankroll, unsigned int minimum)
    {
        return minimum;
    }

    bool draw(Card dealer, const Hand &player)
    {
        auto value = player.handValue();
        if (value.soft)
        {
            if (value.count <= 17)
            {
                return true;
            }
            else if (value.count == 18 && dealer.spot == TWO && !(dealer.spot == SEVEN && dealer.spot == EIGHT))
            {
                return true;
            }
        }
        else
        {
            if (value.count <= 11)
            {
                return true;
            }
            else if (value.count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX))
            {
                return true;
            }
            else if (value.count >= 13 && value.count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX))
            {
                return true;
            }
        }
        return false;
    }

    void expose(Card c)
    { }

    void shuffled()
    { }

};

Player *get_Simple()
{
    return (Player *) new SimplePlayer();
}

class CountingPlayer : public Player
{
private:
    int count;
public:
    CountingPlayer()
    {
        this->shuffled();
    }

    int bet(unsigned int bankroll, unsigned int minimum)
    {
        if (count >= 2 && minimum * 2 <= bankroll)
        {
            return minimum * 2;
        }
        return minimum;
    }

    bool draw(Card dealer, const Hand &player)
    {
        SimplePlayer simple;
        return simple.draw(dealer, player);
    }

    void expose(Card c)
    {
        if (c.spot >= TEN)
        {
            count--;
        }
        else if (c.spot >= 2 || c.spot <= 6)
        {
            count++;
        }
    }

    void shuffled()
    {
        this->count = 0;
    }
};

Player *get_Counting()
{
    return (Player *) new CountingPlayer();
}