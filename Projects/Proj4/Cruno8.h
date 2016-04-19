/*
 * File:    Cruno8.h
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef CRUNO8_H_
#define CRUNO8_H_

#include "card.h"
#include "game.h"

class Game;
class Card;

class Cruno8 : public Card {
public:

    // These aren't necessary for this one, but I wanted
    // to include them to unify the cards.
    static const unsigned int Skip = 15;
    static const unsigned int Reverse = 16;
    static const unsigned int DrawTwo = 17;

    // The two constructors.
    Cruno8();
    Cruno8(unsigned int suit, unsigned int points);


    virtual bool playable(Game *gptr) ;
};

#endif /* CRUNO8_H_ */
