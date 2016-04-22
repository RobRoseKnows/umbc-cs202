/*
 * File:    CrunoReverse.h
 * Author:  Robert
 * Section: 3
 * Created: Apr 21, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef CRUNOREVERSE_H_
#define CRUNOREVERSE_H_

#include "card.h"

class CrunoReverse: public Card {
public:
    static const unsigned int Skip = 15;
    static const unsigned int Reverse = 16;
    static const unsigned int DrawTwo = 17;

    CrunoReverse();

    CrunoReverse(unsigned int suit, unsigned int points);

    // Prints out card.
    virtual string toString();

    virtual void playCard(Game *gptr, Player *pptr);

    // Returns true if suit or number is matching.
    virtual bool playable(Game *gptr) ;

};

#endif /* CRUNOREVERSE_H_ */
