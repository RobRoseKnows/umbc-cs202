/* File: pokerhand.cpp
 * Name: Robert Rose
 * Date: 3/8/16
 * E-mail: robrose2@umbc.edu
 * Section: Thursday 11:30

 CMSC 202 Computer Science II
 Spring 2016 Project 2

 Implementation of PokerHand class.
 See pokerhand.h for documentation.
 */

#include <iostream>
using namespace std;

#include "pokerhand.h"

PokerHand::PokerHand() {
	m_valid = false;
	m_rank = NoRank;

	m_lastCardPoints = 0;
	m_firstPairPoints = 0;
	m_secondPairPoints = 0;
	m_tripletPoints = 0;
	m_quadrupletPoints = 0;
}

PokerHand::PokerHand(Card c0, Card c1, Card c2, Card c3, Card c4) {

	// Store cards
	m_cards[0] = c0;
	m_cards[1] = c1;
	m_cards[2] = c2;
	m_cards[3] = c3;
	m_cards[4] = c4;

	// We have cards.
	// Note: this assumes c0, ..., c4 are valid
	//
	m_valid = true;
	m_rank = NoRank;

	// Default values for "additional information"
	//
	m_lastCardPoints = 0;
	m_firstPairPoints = 0;
	m_secondPairPoints = 0;
	m_tripletPoints = 0;
	m_quadrupletPoints = 0;

	// Don't forget to sort
	//
	sort();
	//cout << "Sort finished fine." << endl;

	// IF YOU WANT THE ALTERNATE CONSTRUCTOR
	// TO DO MORE, PLACE THE CODE AFTER THIS
	// LINE:
	// --------------------------------------

	getRank();
	//cout << "Constructor finished fine." << endl;
}

void PokerHand::sort() {
	for (int startAt = 0; startAt < FIVE; startAt++) {
		int mindex = startAt;
		//cout << startAt << ": ";
		for (int i = startAt; i < FIVE; i++) {
			//cout << i << " ";
			if (m_cards[i].points() < m_cards[mindex].points()) {
				mindex = i;
			}
		}

		Card temp = m_cards[startAt];
		m_cards[startAt] = m_cards[mindex];
		m_cards[mindex] = temp;
		//cout << endl;
	}
}

int PokerHand::cmp(PokerHand &otherHand) {
	if (m_rank < otherHand.getRank()) {
		return -1;
	} else if (m_rank > otherHand.getRank()) {
		return 1;
	} else {
		//It's tied... woah boy...
		switch (m_rank) {
		case RoyalFlush:
			// Since we aren't ranking by suit as well, all Royal Flushes are tied.
			return 0;
			// No need for breaks since we already returned.
		case StraightFlush:
			if (otherHand.m_cards[FIVE - 1].points()
					< m_cards[FIVE - 1].points()) {
				return 1;
			} else if (otherHand.m_cards[FIVE - 1].points()
					> m_cards[FIVE - 1].points()) {
				return -1;
			} else {
				return 0;
			}
			break;
		case FourOfAKind:
			if (otherHand.m_quadrupletPoints < m_quadrupletPoints) {
				return 1;
			} else if (otherHand.m_quadrupletPoints > m_quadrupletPoints) {
				return -1;
			} else {
				if (otherHand.m_lastCardPoints < m_lastCardPoints) {
					return 1;
				} else if (otherHand.m_lastCardPoints > m_lastCardPoints) {
					return -1;
				} else {
					return 0;
				}
			}
		case FullHouse:
			if (otherHand.m_tripletPoints < m_tripletPoints) {
				return 1;
			} else if (otherHand.m_tripletPoints > m_tripletPoints) {
				return -1;
			} else {
				if (otherHand.m_firstPairPoints < m_firstPairPoints) {
					return 1;
				} else if (otherHand.m_firstPairPoints > m_firstPairPoints) {
					return -1;
				} else {
					return 0;
				}
			}
		case Flush:
			for (int i = FIVE - 1; i >= 0; i--) {
				if (otherHand.m_cards[i].points() < m_cards[i].points()) {
					return 1;
				} else if (otherHand.m_cards[i].points()
						> m_cards[i].points()) {
					return -1;
				}
			}
			// If all of them are the same.
			return 0;
		case Straight:
			if (otherHand.m_cards[FIVE - 1].points()
					< m_cards[FIVE - 1].points()) {
				return 1;
			} else if (otherHand.m_cards[FIVE - 1].points()
					> m_cards[FIVE - 1].points()) {
				return -1;
			} else {
				return 0;
			}
		case ThreeOfAKind:
			if (otherHand.m_tripletPoints < m_tripletPoints) {
				return 1;
			} else if (otherHand.m_tripletPoints > m_tripletPoints) {
				return -1;
			} else {
				for (int i = FIVE - 4; i >= 0; i--) {
					if (otherHand.m_cards[i].points() < m_cards[i].points()) {
						return 1;
					} else if (otherHand.m_cards[i].points()
							> m_cards[i].points()) {
						return -1;
					}
				}
				return 0;
			}
		case TwoPair:
			if (otherHand.m_firstPairPoints < m_firstPairPoints) {
				return 1;
			} else if (otherHand.m_firstPairPoints > m_firstPairPoints) {
				return -1;
			} else {
				if (otherHand.m_secondPairPoints < m_secondPairPoints) {
					return 1;
				} else if (otherHand.m_secondPairPoints > m_secondPairPoints) {
					return -1;
				} else {
					if (otherHand.m_lastCardPoints < m_lastCardPoints) {
						return 1;
					} else if (otherHand.m_lastCardPoints > m_lastCardPoints) {
						return -1;
					} else {
						return 0;
					}
				}
			}
		case OnePair:
			if (otherHand.m_firstPairPoints < m_firstPairPoints) {
				return 1;
			} else if (otherHand.m_firstPairPoints > m_firstPairPoints) {
				return -1;
			} else {
				for (int i = FIVE - 3; i >= 0; i--) {
					if (otherHand.m_cards[i].points() < m_cards[i].points()) {
						return 1;
					} else if (otherHand.m_cards[i].points()
							> m_cards[i].points()) {
						return -1;
					}
				}
				return 0;
			}
		case HighCard:
			for (int i = FIVE - 1; i >= 0; i--) {
				if (otherHand.m_cards[i].points() < m_cards[i].points()) {
					return 1;
				} else if (otherHand.m_cards[i].points()
						> m_cards[i].points()) {
					return -1;
				}
			}
			return 0;
		case NoRank:
			// Indeterminate
			return 0;
		default:
			return 0;
		}
	}

}

PokerHand::pRank PokerHand::getRank() {
	if (!m_valid) {
		return NoRank;
	}

	if (m_rank == NoRank) {
		if (isRoyalFlush()) {
			m_rank = RoyalFlush;
			return m_rank;
		}

		//cout << "Past RF" << endl;

		if (isStraightFlush()) {
			m_rank = StraightFlush;
			return m_rank;
		}

		//cout << "Past SF" << endl;

		if (isFourOfAKind()) {
			m_rank = FourOfAKind;
			return m_rank;
		}

		//cout << "Past 4" << endl;

		if (isFullHouse()) {
			m_rank = FullHouse;
			return m_rank;
		}

		//cout << "Past FH" << endl;

		if (isFlush()) {
			m_rank = Flush;
			return m_rank;
		}

		//cout << "Past Flush" << endl;

		if (isStraight()) {
			m_rank = Straight;
			return m_rank;
		}

		//cout << "Past straight" << endl;

		if (isThreeOfAKind()) {
			m_rank = ThreeOfAKind;
			return m_rank;
		}

		//cout << "Past 3" << endl;

		if (isTwoPair()) {
			m_rank = TwoPair;
			return m_rank;
		}

		//cout << "Past 2P" << endl;

		if (isOnePair()) {
			m_rank = OnePair;
			return m_rank;
		}

		//cout << "Past 1P" << endl;

		if (isHighCard()) {
			m_rank = HighCard;
			return m_rank;
		}

		//cout << "Past HC" << endl;
	}

	return m_rank;
}

void PokerHand::printRank() {
	if(!m_valid) {
		cout << "Invalid hand." << endl;
		return;
	}

	switch (m_rank) {
	case RoyalFlush:
		cout << "Royal Flush" << endl;
		break;
	case StraightFlush:
		cout << "Straight Flush" << endl;
		break;
	case FourOfAKind:
		cout << "Four of a Kind" << endl;
		break;
	case FullHouse:
		cout << "Full House" << endl;
		break;
	case Flush:
		cout << "Flush" << endl;
		break;
	case Straight:
		cout << "Straight" << endl;
		break;
	case ThreeOfAKind:
		cout << "Three of a Kind" << endl;
		break;
	case TwoPair:
		cout << "Two Pair" << endl;
		break;
	case OnePair:
		cout << "One Pair" << endl;
		break;
	case HighCard:
		cout << "High Card" << endl;
		break;
	case NoRank:
		cout << "No Rank" << endl;
		break;
	default:
		cout << "Default" << endl;
	}
}

void PokerHand::printCards() {
	if(!m_valid) {
		cout << "Invalid hand." << endl;
	}

	for (int i = 0; i < FIVE; i++) {
		m_cards[i].print();
	}
}

bool PokerHand::isAllOneSuit() {
	Card::cSuit suit = m_cards[0].suit();

	for (int i = 1; i < FIVE; i++) {
		if (suit != m_cards[i].suit()) {
			return false;
		}
	}

	return true;
}

bool PokerHand::isSequence() {
	Card::cPoints prevPoints = m_cards[0].points();

	for (int i = 1; i < FIVE; i++) {
		if (prevPoints == m_cards[i].points() - 1) {
			prevPoints = m_cards[i].points();
		} else {
			return false;
		}
	}

	return true;
}

bool PokerHand::isAllUnique() {
	return m_cards[0].points() != m_cards[1].points()
			&& m_cards[1].points() != m_cards[2].points()
			&& m_cards[2].points() != m_cards[3].points()
			&& m_cards[3].points() != m_cards[4].points();
}

bool PokerHand::isRoyalFlush() {
	if (m_rank == NoRank && m_valid) {
		if (isAllOneSuit() && isSequence()
				&& m_cards[FIVE - 1].points() == 14) {
			m_rank = RoyalFlush;
			return true;
		}
	}

	return m_rank == RoyalFlush;

}

bool PokerHand::isStraightFlush() {
	if (m_rank == NoRank && m_valid) {
		if (isAllOneSuit() && isSequence()
				&& m_cards[FIVE - 1].points() != 14) {
			m_rank = StraightFlush;
			return true;
		}
	}

	return m_rank == StraightFlush;
}

bool PokerHand::isFourOfAKind() {
	if (m_rank == NoRank && m_valid) {
		//Check 1-4
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_lastCardPoints = m_cards[0].points();
			m_quadrupletPoints = m_cards[4].points();
			m_rank = FourOfAKind;
			return true;
		}

		// Check 4-1
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_lastCardPoints = m_cards[4].points();
			m_quadrupletPoints = m_cards[3].points();
			m_rank = FourOfAKind;
			return true;
		}
	}

	return m_rank == FourOfAKind;
}

bool PokerHand::isFullHouse() {
	if (m_rank == NoRank && m_valid) {
		// Check 2-3
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_tripletPoints = m_cards[4].points();
			m_firstPairPoints = m_cards[1].points();
			m_rank = FullHouse;
			return true;
		}

		// Check 3-2
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_tripletPoints = m_cards[2].points();
			m_firstPairPoints = m_cards[4].points();
			m_rank = FullHouse;
			return true;
		}
	}

	return m_rank == FullHouse;
}

bool PokerHand::isFlush() {
	if (m_rank == NoRank && m_valid) {
		if (isAllOneSuit() && !isSequence() && isAllUnique()) {
			m_rank = Flush;
			return true;
		}
	}

	return m_rank == Flush;
}

bool PokerHand::isStraight() {
	if (m_rank == NoRank && m_valid) {
		if (!isAllOneSuit() && isSequence()) {
			m_rank = Straight;
			return true;
		}
	}

	return m_rank == Straight;
}

bool PokerHand::isThreeOfAKind() {
	if (m_rank == NoRank && m_valid) {

		//Check 3-1-1
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_tripletPoints = m_cards[2].points();
			m_rank = ThreeOfAKind;
			return true;
		}

		//Check 1-3-1
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_tripletPoints = m_cards[3].points();
			m_rank = ThreeOfAKind;
			return true;
		}

		//Check 1-1-3
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_tripletPoints = m_cards[4].points();
			m_rank = ThreeOfAKind;
			return true;
		}
	}

	return m_rank == ThreeOfAKind;
}

bool PokerHand::isTwoPair() {
	if (m_rank == NoRank && m_valid) {
		// Check 2-2-1
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_firstPairPoints = m_cards[3].points();
			m_secondPairPoints = m_cards[1].points();
			m_lastCardPoints = m_cards[4].points();
			m_rank = TwoPair;
			return true;
		}

		// Check 2-1-2
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_firstPairPoints = m_cards[4].points();
			m_secondPairPoints = m_cards[1].points();
			m_lastCardPoints = m_cards[2].points();
			m_rank = TwoPair;
			return true;
		}

		// Check 1-2-2
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_firstPairPoints = m_cards[4].points();
			m_secondPairPoints = m_cards[2].points();
			m_lastCardPoints = m_cards[0].points();
			m_rank = TwoPair;
			return true;
		}

	}

	return m_rank == TwoPair;
}

bool PokerHand::isOnePair() {
	if (m_rank == NoRank && m_valid) {
		// Check 2-1-1-1
		if (m_cards[0].points() == m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_firstPairPoints = m_cards[1].points();
			m_rank = OnePair;
			return true;
		}

		// Check 1-2-1-1
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() == m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_firstPairPoints = m_cards[2].points();
			m_rank = OnePair;
			return true;
		}

		// Check 1-1-2-1
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() == m_cards[3].points()
				&& m_cards[3].points() != m_cards[4].points()) {
			m_firstPairPoints = m_cards[3].points();
			m_rank = OnePair;
			return true;
		}

		// Check 1-1-1-2
		if (m_cards[0].points() != m_cards[1].points()
				&& m_cards[1].points() != m_cards[2].points()
				&& m_cards[2].points() != m_cards[3].points()
				&& m_cards[3].points() == m_cards[4].points()) {
			m_firstPairPoints = m_cards[4].points();
			m_rank = OnePair;
			return true;
		}
	}

	return m_rank == OnePair;
}

bool PokerHand::isHighCard() {
	if (m_rank == NoRank && m_valid) {
		if (isAllUnique() && !isAllOneSuit()) {
			m_rank = HighCard;
			return true;
		}
	}

	return m_rank == HighCard;
}
