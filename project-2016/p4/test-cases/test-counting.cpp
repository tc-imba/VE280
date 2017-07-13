#include "card.h"
#include "hand.h"
#include "player.h"
#include <iostream>

using namespace std;

int main()
{
    int minimum = 5;
    int bankroll;
    Player *player = get_Counting();
    Card dealer, card;
    Hand h;

//--------------basic bet-----------------
    bankroll = 10;
    dealer.suit = SPADES;
    dealer.spot = TWO;
    player->expose(dealer); // count = 1
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = HEARTS;
    card.spot = THREE;
    player->expose(card); // count = 2
    if(player->bet(bankroll, minimum) != 2*minimum)
        cout << "error happens" << endl;

    card.suit = HEARTS;
    card.spot = SEVEN;
    player->expose(card); // count = 2
    if(player->bet(bankroll, minimum) != 2*minimum)
        cout << "error happens" << endl;

    card.suit = HEARTS;
    card.spot = JACK;
    player->expose(card); // count = 1
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = HEARTS;
    card.spot = NINE;
    player->expose(card); // count = 1
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = DIAMONDS;
    card.spot = FOUR;
    player->expose(card); // count = 2
    if(player->bet(bankroll, minimum) != 2*minimum)
        cout << "error happens" << endl;

    card.suit = DIAMONDS;
    card.spot = FIVE;
    player->expose(card); // count = 3
    if(player->bet(bankroll, minimum) != 2*minimum)
        cout << "error happens" << endl;

    card.suit = DIAMONDS;
    card.spot = ACE;
    player->expose(card); // count = 2
    if(player->bet(bankroll, minimum) != 2*minimum)
        cout << "error happens" << endl;

    card.suit = DIAMONDS;
    card.spot = QUEEN;
    player->expose(card); // count = 1
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = SPADES;
    card.spot = KING;
    player->expose(card); // count = 0
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = SPADES;
    card.spot = ACE;
    player->expose(card); // count = -1
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

//--------------shuffle-----------------
    bankroll = 10;
    player->shuffled();
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

//--------------not enough bankroll-----------------
    bankroll = 5;
    player->shuffled();
    dealer.suit = SPADES;
    dealer.spot = TWO;
    player->expose(dealer);
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;

    card.suit = HEARTS;
    card.spot = THREE;
    player->expose(card);
    if(player->bet(bankroll, minimum) != minimum)
        cout << "error happens" << endl;
    cout << "exit" << endl;
    return 0;
}
