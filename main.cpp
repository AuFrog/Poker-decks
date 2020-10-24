#include "Card.h"
#include "DeckofCards.h"
#include "HandofCards.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <future>
#include <vector>
#include <thread>

using namespace std;




static const int fiveCard = 5;

/**
*Base score of the ranking
*Base on the score, we can compare who is/are the winner(s)
*/
static const int royalFlush = 9 * 100;
static const int straightFlush = 8 * 100;
static const int fourKind = 7 * 100;
static const int fullHouse = 6 * 100;
static const int flush_ = 5 * 100;
static const int straigh = 4 * 100;
static const int threeKind = 3 * 100;
///two pair==200
///one pair==100
static const int highCard = 0 * 100;




/**
* Count how mamy pairs in the hand of cards
* 
* @param numofPair A counter, count the number of pairs
* @return the tatol unmber of pairs
*/
int pairCard(int* sortFace) {

	int numofPair = 0;

	for (int i = 0;i < fiveCard;i++) {
		if (sortFace[i] == sortFace[i + 1]) {
			numofPair++;
		}
	}

	return numofPair;
}


/**
* Sort the face of the cards first, so we can see the what the hand is (ex,Flush, Stragiht, ...)
* If the Ranking are the same (ex, both two hands are Stright), we consider this as a draw. 
* (No further comparison)
* 
* @param sortFace[] Store only the faces of the hand
* @param sortSuit[] Store only the suits of the hand
* @return the score of the hand
*/
int sortCard(vector<Card> temp) {

	int sortFace[fiveCard];
	int sortSuit[fiveCard];

	/**
	* In his game, at most cases, we only need to compare the faces.
	* So we separete the faces and suits here.
	* And then sort the faces,so that we see what kind of hand it is easily
	*/
	for (int i = 0;i < fiveCard;i++) {
		sortFace[i] = temp[i].getFace();
		sortSuit[i] = temp[i].getSuit();
	}

	for (int i = fiveCard - 1;i >= 0;i--) {
		for (int j = 0;j <= i - 1;j++) {
			if (sortFace[j] > sortFace[j + 1]) {
				int t;
				t = sortFace[j];
				sortFace[j] = sortFace[j + 1];
				sortFace[j + 1] = t;
			}
		}
	}




	///A, K, Q, J, 10, all the same suit, Royal flush 
	if ((sortFace[0] == 1 && sortFace[1] == 10 && sortFace[2] == 11 && sortFace[3] == 12 && sortFace[4] == 13) &&
		(sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
			sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4])) {
		cout << "Royal Flush (A, K, Q, J, 10, all the same suit.)" << endl;

		return royalFlush;
	}


	/// Five cards in a sequence, this may be Straight flush or Straight
	else if (sortFace[0] + 1 == sortFace[1] && sortFace[1] + 1 == sortFace[2] &&
		sortFace[2] + 1 == sortFace[3] && sortFace[3] + 1 == sortFace[4]) {

		///If all the same suit, Straight flush. 
		if (sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
			sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4]) {
			cout << "Straight Flush (same suit sequence)" << endl;

			return straightFlush ;
		}
		///Just a sequence, Straigh
		else {
			cout << "Straight (sequence)" << endl;
			return straigh;
		}
	}


	///All four cards of the same rank, Fout of a kind.
	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2] && sortFace[0] == sortFace[3]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3] && sortFace[1] == sortFace[4])) {
		cout << "Four of a Kind (4 same card)" << endl;

		return fourKind;
	}


	///Three cards of the same rank, this may be Full House or Three of a Kind.
	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3]) ||
		(sortFace[2] == sortFace[3] && sortFace[2] == sortFace[4])) {

		int i = pairCard(sortFace);

		///Three cards with a pair.
		if (i == 3) {
			cout << "Full House (3 same + 1 pair)" << endl;
			return fullHouse;
		}
		///Just three cards of the same rank.
		else {
			cout << "Three of a Kind (3 same)" << endl;
			return threeKind;
		}

	}

	///Call the pairCard function to count how many pairs in this hand.
	else if (int i = pairCard(sortFace)) {
		cout << i << " pairs." << endl;
		return i*100;
	}

	///Any five cards of the same suit, but not in a sequence, Flush. 
	else if (sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
		sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4]) {
		cout << "Flush (same suit)" << endl;
		return flush_;
	}

	///Find the highest card of this hand
	else {
		cout << "the highest card is ";
		int tempH = sortFace[4] + 2;/// +2, because index[0} store face 2, index[1] store face 3 ...

		switch (tempH) {
		case 14:
			cout << "Ace." << endl;
			break;
		case 13:
			cout << "King." << endl;
			break;
		case 12:
			cout << "Queen" << endl;
			break;
		case 11:
			cout << "Jack." << endl;
			break;
		default:
			cout << tempH << endl;
		}
		
		return tempH;
	}

}

/**
* Use a temp vector to store all 4 hands, and then sort it.
* So that we can see the higher ranking hand easily.
* @param temp The temporary vector
* 
*/
void compare(HandofCards d1, HandofCards d2, HandofCards d3, HandofCards d4) {

	vector<HandofCards> temp;
	temp.push_back(d1);
	temp.push_back(d2);
	temp.push_back(d3);
	temp.push_back(d4);

	stable_sort(temp.begin(), temp.end(), less<HandofCards>());

	if (temp[0].getRanking() == temp[1].getRanking() && temp[1].getRanking() == temp[2].getRanking() && temp[2].getRanking() == temp[3].getRanking()) {
		cout << "Four player draw." << endl;
	}
	else if (temp[1].getRanking() == temp[2].getRanking() && temp[2].getRanking() == temp[3].getRanking()) {
		cout << "Player " << temp[1].getName() << ", " << temp[2].getName() << ", " << temp[3].getName() << " are the best (same ranking)." << endl;
	}
	else if (temp[2].getRanking() == temp[3].getRanking()) {
		cout << "Player " << temp[2].getName() << ", " << temp[3].getName() << " are the best (same ranking).";
	}
	else {
		cout << "Player " << temp[3].getName() << " is the best.";
	}
}



int main()

{	
	///Create a deck of cards.
	cout << "********** Game Begin *************" << endl;
	DeckofCards game;
	cout << "************ Shuffle **************"<<endl;
	game.shuffle();
	cout << endl;

	///Use the s1,s2,s3,s4 as share memory.
	string s1 = "POne";
	string s2 = "PTow";
	string s3 = "PThree";
	string s4 = "PFour";

	///Main thread creats 4 hands (as contains to store cards return from slave threads.)
	HandofCards hand_1(s1);
	HandofCards hand_2(s2);
	HandofCards hand_3(s3);
	HandofCards hand_4(s4);
	
	///Create 4 slaves threads, each thread run the deal() functions to get 5 cards
	future<vector<Card>> fu_1 = async(launch::async, &DeckofCards::deal, &game, ref(s1));
	future<vector<Card>> fu_2 = async(launch::async, &DeckofCards::deal, &game, ref(s2));
	future<vector<Card>> fu_3 = async(launch::async, &DeckofCards::deal, &game, ref(s3));
	future<vector<Card>> fu_4 = async(launch::async, &DeckofCards::deal, &game, ref(s4));

	///Slave threads return the cards, and the main threads store them in diffent hands.
	hand_1.setCard (fu_1.get());	
	hand_2.setCard (fu_2.get());
	hand_3.setCard (fu_3.get());
	hand_4.setCard (fu_4.get());
	
	///Print the ranking of each hand and tell who is/are the best
	cout << hand_1.getName() << ", " ;
	hand_1.setRanking(sortCard(hand_1.getCard()));
	cout << hand_2.getName() << ", " ;
	hand_2.setRanking(sortCard(hand_2.getCard()));
	cout << hand_3.getName() << ", " ;
	hand_3.setRanking(sortCard(hand_3.getCard()));
	cout << hand_4.getName() << ", " ;
	hand_4.setRanking(sortCard(hand_4.getCard()));
	cout << endl;

	compare(hand_1, hand_2, hand_3, hand_4);
	cout << endl;


	return 0;
}


