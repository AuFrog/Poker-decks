#include "Card.h"
#include "DeckofCards.h"
#include "HandofCards.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;



static const int fiveCard = 5;
//static const int allCard = 52;

//Base score of the ranking
static const double royalFlush = 9*100;
static const double straightFlush = 8 * 100;
static const double fourKind = 7 * 100;
static const double fullHouse = 6 * 100;
static const double flush_ = 5 * 100;
static const double straigh = 4 * 100;
static const double threeKind = 3 * 100;
//two pair==200
//one pair==100
static const double highCard = 0 * 100;

//Rankong of face = face*10
//Ranking of suit =suit*1


/***Fine how mamy pairs in the hand of cards****/
double pairCard(int* sortFace) {
	double num = 0;
	double totalFaceRank = 0;
	

	for (int i = 0;i < fiveCard;i++) {
		if (sortFace[i] == sortFace[i + 1]) { 
			num++; 
		}
	}

	return num*100+totalFaceRank*10;
}


int sortCard(vector<Card> temp) {
	int sortFace[fiveCard];
	int sortSuit[fiveCard];
	//int finalRanking = 0;

	for (int i = 0;i < fiveCard;i++) {
		sortFace[i] = temp[i].getFace();
		sortSuit[i] = temp[i].getSuit();
	}

	for (int i = fiveCard-1;i >= 0;i--) {
		for (int j = 0;j <= i-1;j++) {
			if (sortFace[j] > sortFace[j + 1]) {
				int t;
				t = sortFace[j];
				sortFace[j] = sortFace[j + 1];
				sortFace[j + 1] = t;
			}		
		}
	}


	/***********test************
	cout << endl;
	cout << "sorted: " << endl;
	for (int i = 0;i < fiveCard;i++) {

		cout << sortFace[i] << endl;
	}
	***********************************/


	/**************Royal flush, puls the score if the suits************/
	if ((sortFace[0] == 1 && sortFace[1] == 10 && sortFace[2] == 11 && sortFace[3] == 12 && sortFace[4] == 13) &&
		(sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
			sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4])) {
		cout << "Royal flush (A, K, Q, J, 10, all the same suit.)" << endl;
		
		return royalFlush + sortSuit[0];
	}


	/*******************Straight flush &Straight***************************/
	else if (sortFace[0] + 1 == sortFace[1] && sortFace[1] + 1 == sortFace[2] &&
		sortFace[2] + 1 == sortFace[3] && sortFace[3] + 1 == sortFace[4]) {

		//Straght flush, plus the score of the highest card and the suit
		if (sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
			sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4]) {
			cout << "Straight flush (same suit sequence)" << endl;

			return straightFlush + sortFace[4] * 10 + sortSuit[0];
		}
		// Straith, plus the score of the highest card and highest card's suit
		else {
			cout << "Straight (sequence)" << endl;
			return straigh + sortFace[4] * 10 + sortSuit[4];
		}
	}


	/******Fout of a kind, plus the score to the same card (face)**********/
	/****The sigle card must at the begining or end, after sorted (xoooo or oooox) ****/
	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2] && sortFace[0] == sortFace[3]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3] && sortFace[1] == sortFace[4])) {
		cout << "Four of a kind (4 same card)" << endl;

		return fourKind + sortFace[2] * 10;
	}


	/****** Fout of a kind, plus the score to the three (face) *****/
	/****************** Patten: xxooo or oooxx ****************************/
	else if ((sortFace[0] == sortFace[1] && sortFace[0] == sortFace[2]) ||
		(sortFace[1] == sortFace[2] && sortFace[1] == sortFace[3]) ||
		(sortFace[2] == sortFace[3] && sortFace[2] == sortFace[4])) {

		int i = pairCard(sortFace);
		if (i == 3) {
			cout << "Full house (3 same + 1 pair)" << endl;
			return fullHouse + sortFace[2] * 10 ;
		}
		else {
			cout << "Three of a kind (3 same)" << endl;
			return threeKind + sortFace[2] * 10 ;
		}

	}


	else if (int i = pairCard(sortFace)) {
		cout << "there are " << i << " pairs." << endl;
		return i;
	}

	else if (sortSuit[0] == sortSuit[1] && sortSuit[1] == sortSuit[2] &&
		sortSuit[2] == sortSuit[3] && sortSuit[3] == sortSuit[4]) {
		cout << "Flush (same suit)" << endl;
		return flush_;
	}

	else {
		if (sortFace[0] == 0) {
			cout << "The hightes card is " << sortFace[0]+1 << endl;
		}
		else {
			cout << "The hightes card is " << sortFace[4]+1 << endl;
		}
		return highCard;
	}

}

void compare(HandofCards d1, HandofCards d2, HandofCards d3, HandofCards d4) {

	vector<HandofCards> a;
	a.push_back(d1);
	a.push_back(d2);
	a.push_back(d3);
	a.push_back(d4);

	
	//for (int i = 0; i < a.size(); i++) {
	//	cout << a[i].getName() << endl;
	//}
	stable_sort(a.begin(), a.end(),less<HandofCards>());

	for (int i = 0; i < a.size(); i++) {
		cout << a[i].getName() << " ranking " << a[i].getRanking() << endl;
	}

	
}


int main()
{
	DeckofCards game;
	HandofCards deck_1("POne");
	HandofCards deck_2("PTow");
	HandofCards deck_3("PThree");
	HandofCards deck_4("PFour");

	//int ranking_1, ranking_2, ranking_3, ranking_4;

	cout << "shuffle" << endl;
	game.shuffle();
	cout << endl;

	cout << "1st deal" << endl;
	deck_1.setCard ( game.deal());
	cout << "sort deck_1" << endl;
	deck_1.setRanking( sortCard(deck_1.getCard()));
	cout << endl;

	cout << "2rd deal" << endl;
	deck_2.setCard(game.deal());
	cout << "sort deck_2" << endl;
	deck_2.setRanking(sortCard(deck_2.getCard()));
	cout << endl;

	cout << "3rd deal" << endl;
	deck_3.setCard(game.deal());
	cout << "sort deck_3" << endl;
	deck_3.setRanking(sortCard(deck_3.getCard()));
	cout << endl;

	cout << "4th deal" << endl;
	deck_4.setCard(game.deal());
	cout << "sort deck_4" << endl;
	deck_4.setRanking( sortCard(deck_4.getCard()));
	cout << endl;

	compare(deck_1, deck_2, deck_3, deck_4);

	return 0;
}


// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
