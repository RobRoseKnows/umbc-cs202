/*
 * File: mytest.cpp
 * Name: Robert Rose
 * Date: 3/10/16
 * E-mail: robrose2@umbc.edu
 * Section: Thursday 11:30
 *
 *  Created on: Mar 9, 2016
 *      Author: Robert
 */

#include<iostream>
#include "pokerhand.h"
#include "card.h"

using namespace std;

// Takes the card suit and returns a string representation of the suit.
string suitToText(Card::cSuit s);
// Takes the card points and returns a string representation of the number of points.
string pointsToText(Card::cPoints p);
// Takes the rank and returns a string representation of the rank.
string rankToText(PokerHand::pRank r);
// Takes the result from PokerHand::cmp() and converts it into a string description of what happened.
string resultToText(int r);

string pointsToText(Card::cPoints p) {
	if (p == 0 || p == p) {
		return "Invalid Card";
	} else if (p >= 2 && p <= 10) {
		return "" + p;
	} else {
		switch (p) {
		case 11:
			return "Jack";
		case 12:
			return "Queen";
		case 13:
			return "King";
		case 14:
			return "Ace";
		default:
			return "Invalid";
		}
	}

}

string suitToText(Card::cSuit s) {
	switch (s) {
	case (Card::Invalid):
		return "Invalid";
	case (Card::Clubs):
		return "Clubs";
	case (Card::Diamonds):
		return "Diamonds";
	case (Card::Hearts):
		return "Hearts";
	case (Card::Spades):
		return "Spades";
	default:
		return "Default";
	}
}

string rankToText(PokerHand::pRank r) {

	switch (r) {
	case PokerHand::RoyalFlush:
		return "Royal Flush";
	case PokerHand::StraightFlush:
		return "Straight Flush";
	case PokerHand::FourOfAKind:
		return "Four of a Kind";
	case PokerHand::FullHouse:
		return "Full House";
	case PokerHand::Flush:
		return "Flush";
	case PokerHand::Straight:
		return "Straight";
	case PokerHand::ThreeOfAKind:
		return "Three of a Kind";
	case PokerHand::TwoPair:
		return "Two Pair";
	case PokerHand::OnePair:
		return "One Pair";
	case PokerHand::HighCard:
		return "High Card";
	case PokerHand::NoRank:
		return "No Rank";
	default:
		return "Default";
	}
}

string resultToText(int r) {
	switch(r) {
	case 1:
		return "Host wins";
	case 0:
		return "Tie";
	case -1:
		return "Host loses";
	default:
		return "Default case";
	}
}

int main() {

	cout << "ALL FUNCTIONS SHOULD WORK." << endl;

	// Call the card constructors
	cout << "Calling card constructors." << endl;
	Card cFour(Card::Clubs, 4);
	Card dFour(Card::Diamonds, 4);
	Card sTen(Card::Spades, 10);
	Card hJack(Card::Hearts, 11);
	Card hQueen(Card::Hearts, 12);
	Card cQueen(Card::Clubs, 12);
	Card sQueen(Card::Spades, 12);
	Card hKing(Card::Hearts, 13);
	Card hAce(Card::Hearts, 14);
	Card defaultConstruct;
	cout << endl;

	cout << "Calling card print methods." << endl;
	sQueen.print();
	cFour.print();
	cQueen.print();
	dFour.print();
	hQueen.print();
	defaultConstruct.print();
	cout << endl;

	cout << "Printing cards using .suit() and .points()" << endl;
	cout << pointsToText(sQueen.points()) << " of " << suitToText(sQueen.suit())
			<< endl;
	cout << pointsToText(cFour.points()) << " of " << suitToText(cFour.suit())
			<< endl;
	cout << pointsToText(cQueen.points()) << " of " << suitToText(cQueen.suit())
			<< endl;
	cout << pointsToText(dFour.points()) << " of " << suitToText(dFour.suit())
			<< endl;
	cout << pointsToText(hQueen.points()) << " of " << suitToText(hQueen.suit())
			<< endl;
	cout << endl;

	cout << "Creating hand and empty hand using constructors" << endl;
	PokerHand emptyHand;
	PokerHand fullHouseQ4(sQueen, cFour, cQueen, dFour, hQueen);
	PokerHand twoPairQ4A(cFour, hQueen, cQueen, dFour, hAce);
	PokerHand twoPairQ4J(dFour, hJack, hQueen, cQueen, cFour);
	PokerHand highAKQ104(dFour, hQueen, hKing, sTen, hAce);
	PokerHand highAKJ104(hKing, sTen, hAce, hJack, cFour);
	cout << endl;

	cout << "Printing cards using PokerHand::printCards()" << endl;
	cout << "Empty Hand:" << endl;
	emptyHand.printCards();
	cout << "Full House Q-4:" << endl;
	fullHouseQ4.printCards();
	cout << "High AKJ104:" << endl;
	highAKJ104.printCards();
	cout << endl;

	cout << "Printing rank using PokerHand::printRank()" << endl;
	emptyHand.printRank();
	fullHouseQ4.printRank();
	cout << endl;

	// All the PokerHand::is...() functions are called in PokerHand::getRank() when it ran in the constructor.
	cout << "Print rank from getRank()" << endl;
	cout << rankToText(emptyHand.getRank()) << endl;
	cout << rankToText(fullHouseQ4.getRank()) << endl;
	cout << endl;

	cout << "Print is___() method results" << endl;
	cout << "isRoyalFlush(): " << fullHouseQ4.isRoyalFlush() << endl;
	cout << "isStraightFlush(): " << fullHouseQ4.isStraightFlush() << endl;
	cout << "isFourOfAKind(): " << fullHouseQ4.isFourOfAKind() << endl;
	cout << "isFullHouse(): " << fullHouseQ4.isFullHouse() << endl;
	cout << "isFlush(): " << fullHouseQ4.isFlush() << endl;
	cout << "isStraight(): " << fullHouseQ4.isStraight() << endl;
	cout << "isThreeOfAKind(): " << fullHouseQ4.isThreeOfAKind() << endl;
	cout << "isTwoPair(): " << fullHouseQ4.isTwoPair() << endl;
	cout << "isOnePair(): " << fullHouseQ4.isOnePair() << endl;
	cout << "isHighCard(): " << fullHouseQ4.isHighCard() << endl;
	cout << "These were called in getRank() when it first ran with NoRank called from the constructor." << endl;
	cout << endl;

	cout << "A couple comparisons.";
	cout << "Empty Host vs. Q-4 FullHouse: " << resultToText(emptyHand.cmp(fullHouseQ4)) << endl;
	cout << "Q-4-A 2P Host vs. Q-4 FullHouse: " << resultToText(twoPairQ4A.cmp(fullHouseQ4)) << endl;
	cout << "Q-4 FH Host vs. Q-4-J 2P: " << resultToText(fullHouseQ4.cmp(twoPairQ4J)) << endl;
	cout << "Q-4-A 2P Host vs. Q-4-J 2P: " << resultToText(twoPairQ4A.cmp(twoPairQ4J)) << endl;
	cout << "A-K-Q-10-4 High Host vs. A-K-J-10-4 High: " << resultToText(highAKQ104.cmp(highAKJ104)) << endl;
	cout << endl;

	return 0;
}

