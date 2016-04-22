/*
 * File:    CrunoDraw2.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The CrunoDraw2 header file.
 */

#ifndef CRUNODRAW2_H_
#define CRUNODRAW2_H_

#include "card.h"
#include "CrunoGame.h"

class Game;
class Player;
class Card;

class CrunoDraw2: public Card {
public:

    // A default constructor for the Draw Two
    // card.
    CrunoDraw2();

    // A constructor for the Draw Two card.
    CrunoDraw2(unsigned int suit, unsigned int points);

    // Prints out card.
    virtual string toString();

    // Calls the super function and then triggers
    // the next player to draw two cards.
    virtual void playCard(Game *gptr, Player *pptr);
};

#endif /* CRUNODRAW2_H_ */
