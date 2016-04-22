/*
 * File:    CrunoSkip.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 18, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The header file for CrunoSkip.
 */

#ifndef CRUNOSKIP_H_
#define CRUNOSKIP_H_

#include "card.h"
#include "CrunoGame.h"

class Game;
class Player;
class Card;

class CrunoSkip: public Card {
public:
    // A default constructor for the Draw Two
    // card. All it does is call Card's constructor.
    CrunoSkip();

    // A constructor for the Draw Two card. All
    // it does is call Card's constructor.
    CrunoSkip(unsigned int suit, unsigned int points);

    // Prints out card.
    virtual string toString();

    // Calls the super function and then sets a
    // variable to store the next player.
    virtual void playCard(Game *gptr, Player *pptr);
};

#endif /* CRUNOSKIP_H_ */
