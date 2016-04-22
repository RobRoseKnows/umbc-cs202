/*
 * File:    CrunoSkip.cpp
 * Author:  Robert Rose
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
    m_points = CrunoGame::Skip;
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


/**
 * Overrode playCard() to tell the game to skip a certain player.
 */
void CrunoSkip::playCard(Game *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);
    CrunoGame *cgptr;
    cgptr = dynamic_cast<CrunoGame *>(gptr);

    // Calls super class to actually play the card.
    Card::playCard(gptr, pptr);

    // This tells the game to skip a certain player number. I chose not
    // to have this actually skip the player because it is better form to
    // do it in such a way that playerAfter() returns the proper next player
    // and so that nextPlayer() won't be called twice.
    cgptr->skipPlayer(gptr->playerAfter(gptr->currentPlayer()));
}


