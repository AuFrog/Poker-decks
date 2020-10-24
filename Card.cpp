#include "Card.h"

Card::Card(int faceNumber, int suitNumber) {
	face = faceNumber;
	suit = suitNumber;
}

string Card::toString() {
	return faceNames[face] + " - " + suitNames[suit];
}


int Card::getFace() { return face;}
int Card::getSuit() { return suit; }

//In this case, the Ace is always 14, higher than King
const string Card::faceNames[faces] = {
	"Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
	"Jack","Queen","King","Ace"
};

const string Card::suitNames[suits] = {
	"Diamond","Heart","Club","Spade"
};