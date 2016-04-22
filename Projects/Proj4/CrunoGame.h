/*
 * File:    CrunoGame.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The header file for CrunoGame.
 */

#ifndef CRUNOGAME_H_
#define CRUNOGAME_H_

#include "game.h"

class Player;
class Card;
class Game;

class CrunoGame : public Game {
public:
    // Constant representing the size of the deck. This is so
    // I can easily add new cards in debugging. I kept it in
    // because it reduces the number of magic numbers.
    static const unsigned int DECK_SIZE = 76;

    // I decided to put these here so that all the card objects
    // could reference to one static set of variables. It made
    // more sense to me than having all of them call one of the
    // other cards since they already include CrunoGame.
    static const unsigned int Skip = 15;
    static const unsigned int Reverse = 16;
    static const unsigned int DrawTwo = 17;

    CrunoGame();

    // Modified initialize method that properly initializes a
    // Cruno game.
    virtual void initialize(int numPlayers) ;

    // Gets the pointer of a player of a given index.
    Player* getPlayerPointer(int index);

    virtual unsigned int nextPlayer() ;

    virtual unsigned int playerAfter(unsigned int thisPlayer) ;

    virtual Card * dealOneCard();

    // Called by CrunoReverse to reverse play
    void reversePlay();

    // Called by CrunoSkip to skip a certain player.
    void skipPlayer(int player);

    // Shuffles the discard into the stock.
    void shuffleCards();

private:
    // Player number to skip. -1 if no skip needed.
    int m_skipPlayerNumber;

    // Constant to add to current player to get next player.
    int m_directionConstant;
};

#endif /* CRUNOGAME_H_ */
