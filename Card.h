#ifndef CARD_H
#define CARD_H

#include<string>
using namespace std;

class Card {
public:
	static const int suits = 4;
	static const int faces = 13;

	Card(int, int);
	int getFace();
	int getSuit();
	string toString();

private:
	int face, suit;
	static const string faceNames[faces];
	static const string suitNames[suits];

};
#endif