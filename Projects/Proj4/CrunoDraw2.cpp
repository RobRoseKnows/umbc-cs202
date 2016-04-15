/*
 * File:    CrunoDraw2.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include<string>
#include<sstream>

using namespace std;

#include "card.h"
#include "player.h"
#include "game.h"
#include "CrunoDraw2.h"

CrunoDraw2::CrunoDraw2() {
    Card::Card();
}

CrunoDraw2::CrunoDraw2(unsigned int s, unsigned int p) {
    Card::Card(s, p);
}

string CrunoDraw2::toString() {
    ostringstream oss;

    switch (Card::m_points) {
        // I included all three Uno cards here so I could
        // just copy and paste this code into the other
        // classes.
        case Skip:
            oss << "Skip";
        case Reverse:
            oss << "Reverse";
        case DrawTwo:
            oss << "Draw Two";
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
            oss << "of INVALID SUIT\n";
    }

    return oss.str();
}

void CrunoDraw2::playCard(Game *gptr, Player *pptr) {
    Card::playCard(gptr, pptr);
    // This records the next player so that the
    // showCardToPlayer() method can properly determine
    // which lucky player gets two more cards!
    m_nextPlayer = gptr->nextPlayer();
}
