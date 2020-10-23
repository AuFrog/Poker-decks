#include "HandofCards.h"


HandofCards::HandofCards(string n) {
	name = n;
}


void HandofCards::setRanking(int r) {
	ranking = r;
}
int HandofCards::getRanking() {
	return ranking;
}

void HandofCards::setCard(vector<Card> c) {
	myCards = c;
};

vector<Card> HandofCards::getCard() {
	return myCards;
}

string HandofCards::getName() {
	return name;
}