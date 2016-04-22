/*
 * File:    Cruno8.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The Crazy 8's wild card header for the game of Cruno.
 */

#ifndef CRUNO8_H_
#define CRUNO8_H_

#include "card.h"
#include "game.h"

class Game;
class Card;

class Cruno8 : public Card {
public:

    // The two constructors.
    Cruno8();
    Cruno8(unsigned int suit, unsigned int points);


    virtual void playCard(Game *gptr, Player *pptr);

    virtual bool playable(Game *gptr) ;

};

#endif /* CRUNO8_H_ */
