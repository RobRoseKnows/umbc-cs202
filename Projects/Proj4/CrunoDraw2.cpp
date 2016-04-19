/*
 * File:    CrunoDraw2.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
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
    m_points = DrawTwo;
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
        // classes.
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

void CrunoDraw2::showPlayerToCard(Player *pptr) {
    // Keep most of the logic in here rather than in playCard. If the
    // card is the next one according to the saved pointer, deal two
    // cards to them.
    if(pptr == m_nextPlayerPtr) {
        cout << "Player " << m_gamePtr->currentPlayer() + 1 << " Draws 2!";

        // Draw the cards.
        Card *c1ptr = m_gamePtr->dealOneCard();
        Card *c2ptr = m_gamePtr->dealOneCard();

        // Give the player their cards.
        pptr->takeCard(c1ptr);
        pptr->takeCard(c2ptr);

        // Print out the player's cards.
        cout << "Player " << m_gamePtr->currentPlayer() + 1 << " draws a card: " << c1ptr->toString() << endl ;
        cout << "Player " << m_gamePtr->currentPlayer() + 1 << " draws a card: " << c2ptr->toString() << endl ;
    }
}

// Might have to change gptr to a CrunoGame.
void CrunoDraw2::playCard(CrunoGame *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);

    // This records the next player so that the showCardToPlayer()
    // method can properly determine which lucky player gets two
    // more cards!
    unsigned int nextPlayerIndex = gptr->currentPlayer() + 1;
    m_nextPlayerPtr = gptr->getPlayerPointer(nextPlayerIndex);
    m_gamePtr = gptr;
}
