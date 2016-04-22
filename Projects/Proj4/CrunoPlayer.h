/*
 * File:    CrunoPlayer.h
 * Author:  Robert
 * Section: 3
 * Created: Apr 22, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef CRUNOPLAYER_H_
#define CRUNOPLAYER_H_

#include "player.h"

using namespace std;

class CrunoPlayer: public Player {
public:
    CrunoPlayer();

    virtual unsigned int pickSuit();

private:
    // These keep track of the number of each suit in the player's
    // hand.
    int m_numClubs;
    int m_numDiamonds;
    int m_numHearts;
    int m_numSpades;


};

#endif /* CRUNOPLAYER_H_ */
