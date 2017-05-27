#include "card.h"
#include "hand.h"
#include "player.h"
#include <iostream>
using namespace std;

int main()
{
    Player *player = get_Simple();
    Card dealer, card;
    Hand h;

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//------------Hard <= 11--------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = NINE;
    h.addCard(card);
    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    card.suit = HEARTS;
    card.spot = TWO;
    h.addCard(card);
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//-----------Hard 12---------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = NINE;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = THREE;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = FOUR;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = FIVE;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

//-----------Hard 13~16----------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = NINE;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = FIVE;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = FOUR;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SIX;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SEVEN;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//-----------Hard >= 17---------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = QUEEN;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = SEVEN;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

//-------Soft < 17-------------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = FIVE;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//-----------Soft 17------------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = SIX;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//------------Soft 18-----------------
    h.discardAll();
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    card.suit = CLUBS;
    card.spot = SEVEN;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = THREE;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SIX;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SEVEN;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = EIGHT;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = NINE;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//--------------Soft >= 19----------------
    h.discardAll();
    card.suit = CLUBS;
    card.spot = EIGHT;
    h.addCard(card);
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

//---------Soft 18-------------
    h.discardAll();
    card.suit = CLUBS;
    card.spot = SIX;
    h.addCard(card);
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    card.suit = DIAMONDS;
    card.spot = ACE;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = THREE;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SIX;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SEVEN;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = EIGHT;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = NINE;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

//---------Hard 13~16-------------
    h.discardAll();
    card.suit = CLUBS;
    card.spot = SIX;
    h.addCard(card);
    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    card.suit = DIAMONDS;
    card.spot = EIGHT;
    h.addCard(card);

    dealer.suit = SPADES;
    dealer.spot = TWO;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = FOUR;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SIX;
    if(player->draw(dealer, h) == true)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = SEVEN;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;

    dealer.suit = SPADES;
    dealer.spot = KING;
    if(player->draw(dealer, h) == false)
        cout << "error happened!" << endl;
    cout << "exit" << endl;
    return 0;
}
