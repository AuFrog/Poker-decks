#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include<vector>
#include"Card.h"

using namespace std;

class DeckofCards {

public:

	static const int allCard = 52;

	/*static const int royalFlush = 10;;
	static const int straightFlush = 9;
	static const int fourKind = 8;
	static const int fullHouse = 7;
	static const int flush = 6;
	static const int straigh = 5;
	static const int threeKind = 4;
	static const int highCard = 1;*/

	DeckofCards();
	void shuffle();
	vector<Card> deal();

	//int sortCard();
	//int pairCard(int* sortFace);
	
private:
	vector<Card> deck;
	int current;

};
#endif // !DECKOFCARDS_H
