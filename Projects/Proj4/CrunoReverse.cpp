/*
 * File:    CrunoReverse.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 21, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "CrunoReverse.h"
#include<sstream>

#include "card.h"
#include "CrunoGame.h"

using namespace std;

CrunoReverse::CrunoReverse() {
    m_points = CrunoGame::Reverse;
    m_suit = Invalid;
}

CrunoReverse::CrunoReverse(unsigned int s, unsigned int p) {
    m_points = p;
    m_suit = s;
}

// Copied from CrunoDraw2.cpp
string CrunoReverse::toString() {
    ostringstream oss;

    switch (m_points) {
        case CrunoGame::Skip:
            oss << "Skip";
            break;
        case CrunoGame::Reverse:
            oss << "Reverse";
            break;
        case CrunoGame::DrawTwo:
            oss << "Draw Two";
            break;
        default:
            // If someone does something really weird, fall
            // back onto whatever the parent method is.
            return Card::toString();
    }

    switch (m_suit) {
        case Clubs:
            oss << " of Clubs";
            break;
        case Diamonds:
            oss << " of Diamonds";
            break;
        case Hearts:
            oss << " of Hearts";
            break;
        case Spades:
            oss << " of Spades";
            break;
        default:
            oss << " of INVALID SUIT\n";
    }

    return oss.str();
}

void CrunoReverse::playCard(Game *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);

    // Dynamic casting!
    CrunoGame *cgptr;
    cgptr = dynamic_cast<CrunoGame *>(gptr);

    cgptr->reversePlay();
}

bool CrunoReverse::playable(Game *gptr) {
    return (m_suit == gptr->currentSuit())
            || (m_points == gptr->currentPoints());
}
