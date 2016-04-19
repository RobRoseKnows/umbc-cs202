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
#include<string>
#include<sstream>

using namespace std;

#include "card.h"
#include "player.h"
#include "CrunoGame.h"

CrunoDraw2::CrunoDraw2() {
    Card::Card();
}

CrunoDraw2::CrunoDraw2(unsigned int s, unsigned int p) {
    Card::Card(s, p);
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
            //return Card::toString();
            oss << m_points;
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
    // I could have put this in playCard but I thought it would be
    // a good idea to keep all of the card action logic here.
    if(pptr == m_nextPlayerPtr) {
        pptr->takeCard(m_gamePtr->dealOneCard());
        pptr->takeCard(m_gamePtr->dealOneCard());
    }
}

// Might have to change gptr to a CrunoGame.
void CrunoDraw2::playCard(CrunoGame *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);
    // This records the next player so that the
    // showCardToPlayer() method can properly determine
    // which lucky player gets two more cards!
    unsigned int nextPlayerIndex = gptr->nextPlayer();
    // TODO: Test this. Chris says that this shouldn't work.
    m_nextPlayerPtr = gptr->getPlayerPointer(nextPlayerIndex);
    m_gamePtr = gptr;
}
