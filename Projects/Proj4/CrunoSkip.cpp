/*
 * File:    CrunoSkip.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 18, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * This is the Skip action card for the Cruno game. A large part of
 * the code is copied from the CrunoDraw2.cpp
 */

#include "CrunoSkip.h"
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

#include "card.h"
#include "player.h"
#include "CrunoGame.h"

CrunoSkip::CrunoSkip() {
    m_points = DrawTwo;
    m_suit = Invalid;
}

CrunoSkip::CrunoSkip(unsigned int s, unsigned int p) {
    m_points = p;
    m_suit = s;
}

// Copied from CrunoDraw2.cpp
string CrunoSkip::toString() {
    ostringstream oss;

    switch (m_points) {
        case Skip:
            oss << "Skip";
            break;
        case Reverse:
            oss << "Reverse";
            break;
        case DrawTwo:
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


// Might have to change gptr to a CrunoGame.
void CrunoSkip::playCard(Game *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);
    CrunoGame *cgptr;
    cgptr = dynamic_cast<CrunoGame *>(gptr);

    Card::playCard(gptr, pptr);
    cgptr->skipPlayer(gptr->playerAfter(gptr->currentPlayer()));
}


