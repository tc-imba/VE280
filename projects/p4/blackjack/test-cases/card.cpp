#include "card.h"
#include <iostream>
using namespace std;

const char *SuitNames[] = {"Spades", "Hearts", "Clubs", "Diamonds"};

const char *SpotNames[] = {"Two", "Three", "Four", "Five", "Six", 
                           "Seven", "Eight", "Nine", "Ten", "Jack", 
                           "Queen", "King", "Ace"};

void displayCard(Card card)
{
    cout << SpotNames[card.spot] << " of " << SuitNames[card.suit]
        << flush;
}
