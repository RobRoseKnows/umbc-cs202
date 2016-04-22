/*
 * File:    CrunoPlayer.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 22, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The header file for the CrunoPlayer class.
 */

#ifndef CRUNOPLAYER_H_
#define CRUNOPLAYER_H_

#include "player.h"

using namespace std;

class Player;
class Game;

class CrunoPlayer: public Player {
public:

    // These are all
    static const int SUIT_MULTIPLIER = 4;
    static const int POINT_MULTIPLIER = 1;
    static const int C8_CONSTANT = 1;
    static const int DRAW2_CONSTANT = 15;
    static const int SKIP_CONSTANT = 11;
    static const int REV_CONSTANT = 10;

    CrunoPlayer(Game *gptr, unsigned int numCards);

    virtual ~CrunoPlayer();

    // Picks the players prefered suit.
    virtual unsigned int pickSuit();

    // add card to our hand. Use this when dealing
    // cards to players or when players have to draw
    // cards.
    //
    virtual void takeCard(Card *cptr) ;


    // main game playing strategy goes here.
    // Which card should we play? return NULL if we want to draw a card.
    // Basic implementation just plays the first playable card and uses
    // no strategy beyond that.  Override to implement different behavior.
    //
    virtual Card *playOneCard(bool &lastCard, bool &oneCardLeft) ;

    // Takes a suit ID and returns the number of cards in the suit.
    unsigned int getCardsInSuit(unsigned int suit);

    float getCardValue(Card* card);

    unsigned int suitWithMostCards();

private:
    // These keep track of the number of each suit in the player's
    // hand.
    int m_numClubs;
    int m_numDiamonds;
    int m_numHearts;
    int m_numSpades;

    void incrementSuit(unsigned int suit);
    void decrementSuit(unsigned int suit);
};

#endif /* CRUNOPLAYER_H_ */
