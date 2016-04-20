/*
 * File:    CrunoDraw2.h
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
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
    static const unsigned int Skip = 15;
    static const unsigned int Reverse = 16;
    static const unsigned int DrawTwo = 17;

    // A default constructor for the Draw Two
    // card. All it does is call Card's constructor.
    CrunoDraw2();

    // A constructor for the Draw Two card. All
    // it does is call Card's constructor.
    CrunoDraw2(unsigned int suit, unsigned int points);

    // Prints out card.
    virtual string toString();

    // Calls the super function and then sets a
    // variable to store the next player.
    virtual void playCard(Game *gptr, Player *pptr);
};

#endif /* CRUNODRAW2_H_ */
