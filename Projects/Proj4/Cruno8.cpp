/*
 * File:    Cruno8.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "card.h"
#include "Cruno8.h"

using namespace std;

Cruno8::Cruno8() {
    Card::Card();
}

Cruno8::Cruno8(unsigned int s, unsigned int p) {
    Card::Card(s, p);
}

// Crazy8 is always valid.
bool Cruno8::playable(Game *gptr) {
    return true;
}
