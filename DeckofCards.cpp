#include "DeckofCards.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int usedCard = 0;

/*Genarate a deck of cards (total 52)*/
DeckofCards::DeckofCards() {
	for (int i = 0;i < allCard;i++) {
		Card card(i % Card::faces, i / Card::faces);
		deck.push_back(card);
	}
}


void DeckofCards::shuffle() {
	srand(time(0));

	int swapRandom[allCard];

	for (int i = 0;i < allCard;i++) {
		swapRandom[i] = int(rand()) % allCard;
	}

	for (int i = 0;i < allCard;i++) {
		Card swapCard(0, 0);
		swapCard = deck[i];
		deck[i] = deck[swapRandom[i]];
		deck[swapRandom[i]] = swapCard;
	}

}

vector<Card> DeckofCards::deal(string& s) {
//vector<Card> DeckofCards::deal() {

	std::lock_guard<std::mutex> lockGuard(mutex);

	if (usedCard == 50) {
			cout << " Card is not enough for a next deal." << endl;
	}

	vector<Card> temp;

	for (int i = 0;i < 5;i++) {
		temp.push_back(deck[i + usedCard]);
		cout <<"thread ID: " <<std::this_thread::get_id() << endl;
		cout <<"Here is "<<s<<" "<<deck[i+usedCard].toString() << endl;
	}
	cout << endl;

	usedCard = usedCard + 5;
	
	return temp;
}

