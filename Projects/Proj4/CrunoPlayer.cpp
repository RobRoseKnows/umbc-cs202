/*
 * File:    CrunoPlayer.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 22, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * This is the CrunoPlayer file that implement player strategies for the
 * game of Cruno.
 */

#include "CrunoPlayer.h"
#include "CrunoGame.h"
#include "player.h"
#include "card.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


CrunoPlayer::CrunoPlayer(Game *gptr, unsigned int numCards): Player(gptr, numCards) {


    // Custom variables.
    m_numClubs = 0;
    m_numDiamonds = 0;
    m_numHearts = 0;
    m_numSpades = 0;
}

CrunoPlayer::~CrunoPlayer() {
    for (unsigned int i=0 ; i < m_numCards ; i++) {
       delete m_cards[i] ;
    }
    delete [] m_cards ;
}

// Returns the suit that the player has the most cards in.
unsigned int CrunoPlayer::pickSuit() {
    return suitWithMostCards();
}

/**
 * This is a helper function that gets the number of cards in
 * a certain suit given as an input.
 */
unsigned int CrunoPlayer::getCardsInSuit(unsigned int suit) {
    switch (suit) {
        case Card::Clubs:
            return m_numClubs;
        case Card::Diamonds:
            return m_numDiamonds;
        case Card::Hearts:
            return m_numHearts;
        case Card::Spades:
            return m_numSpades;
        default:
            return 0;
    }
}

/**
 * This function uses conditionals to return the suit with the
 * most number of cards.
 */
unsigned int CrunoPlayer::suitWithMostCards() {
    unsigned int suitWithMost = Card::Invalid;

    if (m_numClubs >= getCardsInSuit(suitWithMost)) {
        suitWithMost = Card::Clubs;
    }

    if (m_numDiamonds >= getCardsInSuit(suitWithMost)) {
        suitWithMost = Card::Diamonds;
    }

    if (m_numHearts >= getCardsInSuit(suitWithMost)) {
        suitWithMost = Card::Hearts;
    }

    if (m_numSpades >= getCardsInSuit(suitWithMost)) {
        suitWithMost = Card::Spades;
    }

    if (suitWithMost == Card::Invalid) {
        //Sanity check just in case.
        cerr << "Something went wrong in CrunoPlayer::suitWithMostCards()"
                << endl;
        suitWithMost = Card::Spades;
    }

    return suitWithMost;
}

// Add given card to our hand
//
void CrunoPlayer::takeCard(Card *cptr) {
    m_cards[m_numCards] = cptr;
    m_numCards++;
    incrementSuit(cptr->getSuit());


    // sanity check
    //
    if (m_numCards == m_maxCards) {
        cerr << "Something is wrong in Player::takeCard !!!\n";
        exit(1);
    }
}

// Main game playing strategy goes here. However, this implementation
// just plays the first playable card.
//
Card *CrunoPlayer::playOneCard(bool &lastCard, bool &oneCardLeft) {

    unsigned int c;
    Card *cptr, *temp;

    // find first card that is playable

    c = 0;        // index into array of Card pointers
    cptr = NULL;  // haven't found a playable card yet

    // Tries to find cards until the end of the array.
    while (c < m_numCards) {

        if (m_cards[c]->playable(m_game)) { // found playable card

            // If we haven't selected a card already, take this one.
            if(cptr == NULL) {
                cptr = m_cards[c];
            } else if(getCardValue(m_cards[c]) > getCardValue(cptr)){
                // I decided to use an else if here because the two conditionals
                // are independent ideas.
                cptr = m_cards[c];
            }
        }

        c++;    // no pun intended <-- that pun was absoultely intended.
    }

    // If we found a card.
    if (cptr != NULL) {
        m_numCards--;                       // one less card
        m_cards[c] = m_cards[m_numCards];   // replace with last card
        m_cards[m_numCards] = NULL;         // just to be safe

        decrementSuit(cptr->getSuit());

        if (m_numCards == 1)
            oneCardLeft = true;  // say "Uno"?
        if (m_numCards == 0)
            lastCard = true;     // did we win?
    }

    // If it returns NULL, then the Game will make the player draw a card.
    return cptr;

}

/**
 * This method uses constants defined in the header file to calculate
 * the "value" of a card.
 */
float CrunoPlayer::getCardValue(Card *card) {
    float value = 0;

    // Players
    value += getCardsInSuit(card->getSuit()) * SUIT_MULTIPLIER;

    switch(card->getPoints()) {
        case 8:
            // We want to save Crazy 8's for later since they can be played on
            // anything and we aren't playing by the rules that you can't play
            // crazy 8's last.
            value += C8_CONSTANT;
            break;
        case CrunoGame::DrawTwo:
            value += DRAW2_CONSTANT;
            break;
        case CrunoGame::Skip:
            value += SKIP_CONSTANT;
            break;
        case CrunoGame::Reverse:
            value += REV_CONSTANT;
            break;
        case Card::Jack: case Card::Queen:
        case Card::King: case Card::Spades:
            // Make sure the penalties for face cards are correct.
            value += 10 * POINT_MULTIPLIER;
        default:
            // The players will want to get higher value cards out of their hands,
            value += card->getPoints() * POINT_MULTIPLIER;
    }

    return value;
}

/**
 * Private helper function to increment the number of cards of a
 * certain suit.
 */
void CrunoPlayer::incrementSuit(unsigned int suit) {
    switch (suit) {
        case Card::Clubs:
            m_numClubs++;
            break;
        case Card::Diamonds:
            m_numDiamonds++;
            break;
        case Card::Hearts:
            m_numHearts++;
            break;
        case Card::Spades:
            m_numSpades++;
            break;
        default:
            // Do nothing.
            break;
    }
}

/**
 * Private helper function to decrement the number of cards of a
 * certain suit.
 */
void CrunoPlayer::decrementSuit(unsigned int suit) {
    switch (suit) {
        case Card::Clubs:
            m_numClubs--;
            break;
        case Card::Diamonds:
            m_numDiamonds--;
            break;
        case Card::Hearts:
            m_numHearts--;
            break;
        case Card::Spades:
            m_numSpades--;
            break;
        default:
            // Do nothing.
            break;
    }
}
