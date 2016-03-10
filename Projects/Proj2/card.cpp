/* File: card.cpp
 * Name: Robert Rose
 * Date: 3/8/16
 * E-mail: robrose2@umbc.edu
 * Section: Thursday 11:30

 CMSC 202 Computer Science II
 Spring 2016 Project 2

 Implementation of Card member functions.
 See card.h for documentation.

 */

#include <iostream>
#include <string>
#include "card.h"

using namespace std;

// Default constructor marks card as invalid
//
Card::Card() {
	m_suit = Invalid;
	m_points = 0;
}

Card::Card(cSuit s, cPoints p) {

	if (s == Clubs || s == Diamonds || s == Hearts || s == Spades) {
		m_suit = s;
	} else {
		m_suit = Invalid;
		m_points = 0;
	}

	if (p >= 1 && p <= 14 && m_suit != Invalid) {
		m_points = p;
	} else {
		m_suit = Invalid;
		m_points = 0;
	}

}

Card::cPoints Card::points() {

	return m_points;

}

Card::cSuit Card::suit() {

	return m_suit;

}

void Card::print() {

	// Check to make sure the card isn't invalid.
	if (m_points == 0 || m_suit == Invalid) {
		cout << "Invalid Card";
	} else if (m_points >= 2 && m_points <= 10) {
		cout << m_points;
	} else {
		switch (m_points) {
		case 11:
			cout << "Jack";
			break;
		case 12:
			cout << "Queen";
			break;
		case 13:
			cout << "King";
			break;
		case 14:
			cout << "Ace";
			break;
		default:
			cout << "Invalid";
			break;
		}
	}

	cout << " of ";

	switch (m_suit) {
	case (Invalid):
		cout << "Invalid";
		break;
	case (Clubs):
		cout << "Clubs";
		break;
	case (Diamonds):
		cout << "Diamonds";
		break;
	case (Hearts):
		cout << "Hearts";
		break;
	case (Spades):
		cout << "Spades";
		break;
	default:
		cout << "Default";
		break;
	}

	cout << endl;

}
