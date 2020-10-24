#ifndef HANDOFCARDS_H
#define HANDOFCARDS_H

#include"Card.h"

#include<vector>
#include<string>
using namespace std;

class HandofCards {
public:


	HandofCards(string n );
	int getRanking();
	void setRanking(int r);

	void setCard(vector<Card> c);
	vector<Card> getCard();

	string getName();

	bool operator < (const HandofCards &m)const {
		return ranking < m.ranking;
	}



private:
	string name;
	int ranking;

	vector<Card> myCards;

};
#endif
