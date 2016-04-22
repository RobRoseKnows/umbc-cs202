/*
 * File:    Cruno8.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The Crazy 8's wildcard class. This card can be played on anything
 * and allows the player to choose the next suit.
 */

#include "card.h"
#include "Cruno8.h"
#include "CrunoPlayer.h"

using namespace std;

Cruno8::Cruno8() {
    m_points = 8;
    m_suit = Invalid;
}

Cruno8::Cruno8(unsigned int s, unsigned int p) {
    m_points = 8;
    m_suit = s;
}

/**
 * Crazy 8's can always be played
 */
bool Cruno8::playable(Game *gptr) {
    return true;
}

void Cruno8::playCard(Game *gptr, Player *pptr) {
    gptr->setSuit(pptr->pickSuit()) ;

    // Announce the suit has changed.
    switch(pptr->pickSuit()) {
        case Clubs:
            cout << "Player " << gptr->currentPlayer() << " switched to Clubs!";
            break;
        case Hearts:
            cout << "Player " << gptr->currentPlayer() << " switched to Hearts!";
            break;
        case Diamonds:
            cout << "Player " << gptr->currentPlayer() << " switched to Diamonds!";
            break;
        case Spades:
            cout << "Player " << gptr->currentPlayer() << " switched to Spades!";
            break;
    }

    gptr->setPoints(m_points) ;
   return ;
}
