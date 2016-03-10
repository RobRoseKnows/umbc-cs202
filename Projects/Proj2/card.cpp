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

	string output = "";

	// Check to make sure the card isn't invalid.
	if (m_points == 0 || m_suit == Invalid) {
		output = "Invalid Card";
	} else {
		switch (m_points) {
		//For some reason, I needed to do this to get the numbered cards working.
		case 2:
			output += "2";
			break;
		case 3:
			output += "3";
			break;
		case 4:
			output += "4";
			break;
		case 5:
			output += "5";
			break;
		case 6:
			output += "6";
			break;
		case 7:
			output += "7";
			break;
		case 8:
			output += "8";
			break;
		case 9:
			output += "9";
			break;
		case 10:
			output += "10";
			break;
		case 11:
			output += "Jack";
			break;
		case 12:
			output += "Queen";
			break;
		case 13:
			output += "King";
			break;
		case 14:
			output += "Ace";
			break;
		default:
			output += "Invalid";
			break;

		}

		output += " of ";

		switch (m_suit) {
		case (Invalid):
			output += "Invalid";
			break;
		case (Clubs):
			output += "Clubs";
			break;
		case (Diamonds):
			output += "Diamonds";
			break;
		case (Hearts):
			output += "Hearts";
			break;
		case (Spades):
			output += "Spades";
			break;
		default:
			output += "Default";
			break;
		}
	}

	cout << output << endl;

}
