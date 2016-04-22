/*
 * File:    CrunoDraw2.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * This is the Draw 2 implementation for a game of Cruno. The card can
 * be played on any card of the same suit or on another Draw 2 card. The
 * logic for making a player draw 2 is in playCard.
 */

#include "CrunoDraw2.h"
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

#include "card.h"
#include "player.h"
#include "CrunoGame.h"

CrunoDraw2::CrunoDraw2() {
    m_points = CrunoGame::DrawTwo;
    m_suit = Invalid;
}

CrunoDraw2::CrunoDraw2(unsigned int s, unsigned int p) {
    m_points = p;
    m_suit = s;
}

string CrunoDraw2::toString() {
    ostringstream oss;

    switch (m_points) {
        // I included all three Uno cards here so I could
        // just copy and paste this code into the other
        // classses.
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

// Might have to change gptr to a CrunoGame.
void CrunoDraw2::playCard(Game *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);
    CrunoGame *cgptr;
    cgptr = dynamic_cast<CrunoGame *>(gptr);

    // Get a pointer for the next player.
    unsigned int nextPlayerIndex = gptr->playerAfter(gptr->currentPlayer());
    Player *npptr = cgptr->getPlayerPointer(nextPlayerIndex);

    cout << "Player " << cgptr->playerAfter(cgptr->currentPlayer())
            << " Draws 2!" << endl;

    // Originally had all this logic in showPlayerToCard but since that is
    // called before playCard() I moved it to here.

    // Draw the cards.
    Card *c1ptr = cgptr->dealOneCard();
    Card *c2ptr = cgptr->dealOneCard();

    // Give the player their cards.
    npptr->takeCard(c1ptr);
    npptr->takeCard(c2ptr);

    // Print out the player's cards.
    cout << "Player " << cgptr->playerAfter(cgptr->currentPlayer())
            << " draws a card: " << c1ptr->toString() << endl;
    cout << "Player " << cgptr->playerAfter(cgptr->currentPlayer())
            << " draws a card: " << c2ptr->toString() << endl;

}
