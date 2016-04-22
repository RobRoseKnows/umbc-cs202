/*
 * File:    CrunoReverse.h
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 21, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * The header file for the CrunoReverse card.
 */

#ifndef CRUNOREVERSE_H_
#define CRUNOREVERSE_H_

#include "card.h"

class CrunoReverse: public Card {
public:

    CrunoReverse();

    CrunoReverse(unsigned int suit, unsigned int points);

    // Prints out card.
    virtual string toString();

    virtual void playCard(Game *gptr, Player *pptr);

    // Returns true if suit or number is matching.
    virtual bool playable(Game *gptr) ;

};

#endif /* CRUNOREVERSE_H_ */
