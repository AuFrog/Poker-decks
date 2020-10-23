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


vector<Card> DeckofCards::deal() {

	if (usedCard == 50) {
			cout << " Card is not enough for a next deal." << endl;
		}

	vector<Card> temp;

	for (int i = 0;i < 5;i++) {
		temp.push_back(deck[i + usedCard]);
		cout << deck[i+usedCard].toString() << endl;
	}

	usedCard = usedCard + 5;
	//cout << "have use " << usedCard << endl;
	
	return temp;
}

/*int DeckofCards::sortCard() {
	int sortFace[fiveCard];
	int sortSuit[fiveCard];

	for (int i = 0;i < fiveCard;i++) {
		sortFace[i] = deck[i].getFace();
		sortSuit[i] = deck[i].getSuit();
	}

	for (int i = fiveCard;i >= 0;i--) {
		for (int j = 0;j <= 1;j++) {
			int t;
			t = sortFace[j];
			sortFace[j] = sortFace[j + 1];
			sortFace[j + 1] = t;
		}
	}

	if ((sortFace[0]==1 && sortFace[1]==10 && sortFace[2]==11 && sortFace[3]==12 && sortFace[4]==13 )&& 
		(sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
		sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4])) {
		cout << "Royal flush (A, K, Q, J, 10, all the same suit.)" << endl;
		return royalFlush;
	}

	else if (sortFace[0]+1 == sortFace[1] && sortFace[1]+1 == sortFace[2] && 
		sortFace[2]+1 == sortFace[3] && sortFace[3]+1 == sortFace[4]){
		
		if (sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2]&&
			sortSuit[2] == sortSuit[3] && sortSuit[3]== sortSuit[4]) {
			cout << "Straight flush (same suit sequence)" << endl;
			return straightFlush;

		}
		else { 
			cout << "Straight (sequence)" << endl; 
			return straigh;
		}
	}

	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2] && sortFace[0] == sortFace[3]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3] && sortFace[1] == sortFace[4])) {
		cout << "Four of a kind (4 same card)" << endl;
		return fourKind;
	}

	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3]) ||
		(sortFace[2] == sortFace[3] && sortFace[2] == sortFace[4])) {
		
		int i = pairCard(sortFace);
		if (i==3) {
			cout << "Full house (3 same + 1 pair)" << endl;
			return fullHouse;
		}
		else { 
			cout << "Three of a kind (3 same)" << endl;
			return threeKind;
		}

	}

	else if (int i = pairCard(sortFace)) {
		cout << "there are " << i << " pairs." << endl;
		return i;
	}

	else if(sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
		sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4]) {
		cout << "Flush (same suit)" << endl;
		return flush;
	}

	else {
		cout << "The hightes card is "<<sortSuit[4] << endl;
		return highCard;
	}
		
}

int DeckofCards::pairCard(int* sortFace) {
	int num = 0;

	for (int i = 0;i < fiveCard - 1;i++) {
		if (sortFace[i] == sortFace[i + 1]) { num++; }
	}

	return num;
}*/