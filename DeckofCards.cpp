#include "DeckofCards.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int usedCard = 0;

/**
* Genarate a deck of cards (total 52)
*/
DeckofCards::DeckofCards() {
	for (int i = 0;i < allCard;i++) {
		Card card(i % Card::faces, i / Card::faces);
		deck.push_back(card);
	}
}

/**
* Shuffle the deck
*/
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

/**
* Use a temp vector as a container, store the cards that will be give to a slave thread.
* Each time put the top card of the deck into the temp vector,
* and than remove the top card as a used card.
* Use lock_guard to make sure only one thread access the function at the same time
* Print out the name of the current hand asking for cards,
* and the current thread id.
* 
* @param temp The temp container
* @return The temp with five cards
*/
vector<Card> DeckofCards::deal(string& s) {


	std::lock_guard<std::mutex> lockGuard(mutex);

	//if (usedCard == 50) {
	//		cout << " Card is not enough for a next deal." << endl;
	//}

	vector<Card> temp;
	cout << "Here is " << s << endl;


	for (int i = 0;i < 5;i++) {
		temp.push_back(deck[i + usedCard]);

		//temp.push_back(deck[0]);

		cout << "thread ID: " << std::this_thread::get_id() << endl;
		cout << deck[i + usedCard].toString() << endl;

		//deck.erase(deck.begin());

	}

	usedCard = usedCard + 5;
	

	cout << endl;
	return temp;
}

