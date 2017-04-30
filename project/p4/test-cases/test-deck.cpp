#include "deck.h"
#include "card.h"
#include <iostream>
using namespace std;

int main() {
	Deck d;
	Card deal;
	for (int i = 0; i < 20; i++)
	{
		deal = d.deal();
		cout << SpotNames[deal.spot] << " " << SuitNames[deal.suit] << endl;
	}
	cout << "Cards left: " << d.cardsLeft() << endl;
	d.shuffle(20);
	d.shuffle(15);
	d.shuffle(0);
	d.shuffle(52);
	d.shuffle(25);
	for (int i = 0; i < 20; i++) {
		deal = d.deal();
		cout << SpotNames[deal.spot] << " " << SuitNames[deal.suit] << endl;
	}
	d.reset();
	cout << "Cards left: " << d.cardsLeft() << endl;
		
	return 0;
}
