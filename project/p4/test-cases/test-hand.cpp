#include <iostream>
#include "card.h"
#include "hand.h"
#include <iostream>
using namespace std;

int main()
{
    Hand h;
    Card card;

    // initial hand
    // h.displayHand();
    if(h.handValue().count != 0 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    // cout << "Check basic cards" << endl;
    card.suit = SPADES;
    card.spot = TWO;
    h.addCard(card);
    if(h.handValue().count != 2 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = HEARTS;
    card.spot = EIGHT;
    h.addCard(card);
    if(h.handValue().count != 10 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = QUEEN;
    h.addCard(card);
    if(h.handValue().count != 20 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = KING;
    h.addCard(card);
    if(h.handValue().count != 30 || h.handValue().soft != false)
        cout << "error happens" << endl;;
        
    /*
        Check one ACE situation
    */
    h.discardAll();
    if(h.handValue().count != 0 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = SPADES;
    card.spot = THREE;
    h.addCard(card);
    if(h.handValue().count != 3 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 14 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = SEVEN;
    h.addCard(card);
    if(h.handValue().count != 21 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    /*
        Check one ACE situation
    */
    h.discardAll();
    if(h.handValue().count != 0 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = SPADES;
    card.spot = THREE;
    h.addCard(card);
    if(h.handValue().count != 3 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = NINE;
    h.addCard(card);
    if(h.handValue().count != 12 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 13 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    /*
        Check one ACE situation
    */
    h.discardAll();
    if(h.handValue().count != 0 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = HEARTS;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 11 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = SPADES;
    card.spot = JACK;
    h.addCard(card);
    if(h.handValue().count != 21 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = SPADES;
    card.spot = EIGHT;
    h.addCard(card);
    if(h.handValue().count != 19 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    card.suit = SPADES;
    card.spot = TWO;
    h.addCard(card);
    if(h.handValue().count != 21 || h.handValue().soft != false)
        cout << "error happens" << endl;;

    /*
        Check two ACE situation
    */
    h.discardAll();
    card.suit = SPADES;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 11 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 12 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    /*
        Check two ACE situation
    */
    h.discardAll();
    card.suit = SPADES;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 11 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = KING;
    h.addCard(card);
    if(h.handValue().count != 21 || h.handValue().soft != true)
        cout << "error happens" << endl;;

    card.suit = CLUBS;
    card.spot = ACE;
    h.addCard(card);
    if(h.handValue().count != 12 || h.handValue().soft != false)
        cout << "error happens" << endl;;
    cout << "exit" << endl;
    return 0;
}
