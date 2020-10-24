#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include<vector>
#include<thread>
#include<mutex>
#include"Card.h"

using namespace std;

class DeckofCards {

public:

	static const int allCard = 52;
	DeckofCards();
	void shuffle();
	vector<Card> deal(string& s);

	
private:

	vector<Card> deck;
	mutex mutex;
};
#endif // !DECKOFCARDS_H
