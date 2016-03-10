/*
 * test.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: Robert
 */

#include<iostream>
#include "pokerhand.h"

using namespace std;

int main() {
	Card c0(Card::Spades,   12) ;
	Card c1(Card::Clubs,     4) ;
	Card c2(Card::Clubs,    12) ;
	Card c3(Card::Diamonds,  4) ;
	Card c4(Card::Hearts,   12) ;

	PokerHand myHand(c0, c1, c2, c3, c4) ;
	myHand.printCards();
	myHand.printRank();
	return 0;
}

