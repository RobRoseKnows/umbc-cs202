/*
 * File:    CrunoGame.h
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef CRUNOGAME_H_
#define CRUNOGAME_H_

#include "game.h"

class Player;
class Card;
class Game;

class CrunoGame : public Game {
public:
    CrunoGame();

    virtual void initialize(int numPlayers) ;

    Player* getPlayerPointer(int index);

    static const unsigned int DECK_SIZE = 56;
};

#endif /* CRUNOGAME_H_ */
