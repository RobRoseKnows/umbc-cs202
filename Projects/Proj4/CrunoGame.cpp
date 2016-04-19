/*
 * File:    CrunoGame.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "CrunoGame.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "game.h"
#include "CrunoDraw2.h"
#include "Cruno8.h"

// A little helper function to quit the program if
// memory is not allocated. Here "static" means only
// code in this file can see this function.
//
static void ifNullCrash(void *ptr) {
    if (ptr == NULL) {
        cerr << "Could not allocate memory\n";
        exit(1);
    }
    return;
}

CrunoGame::CrunoGame() {
    Game::Game();
}

Player* CrunoGame::getPlayerPointer(int index) {
    return Game::m_players[index];
}

void CrunoGame::initialize(int numPlayers) {
    m_suit = 0;
    m_points = 0;
    m_currentPlayer = 0;

    // can't play by yourself
    //
    if (numPlayers < 2) {
        cerr << "Insufficient players\n";
        exit(1);
    }

    // not enough cards to make it fun for >10.
    //
    if (numPlayers > 10) {
        cerr << "Too many players\n";
        exit(1);
    }

    m_numPlayers = 0;  // no players added yet.

    // allocate space for max requested
    //
    m_maxPlayers = numPlayers;
    m_players = new Player*[numPlayers];
    ifNullCrash(m_players);

    m_winner = m_maxPlayers + 1;  // not a real player

    // usually use just one deck
    int decks = 1;
    m_maxCards = DECK_SIZE;   // 52 cards in one deck

    if (numPlayers > 5) {
        // use two decks
        decks = 2;
        m_maxCards = 2 * DECK_SIZE; // 104 cards in two decks
    }

    // allocate space for the discard pile
    m_discard = new Card*[m_maxCards];
    ifNullCrash(m_discard);
    m_numDiscard = 0;  // nothing discarded yet

    // allocate space for the stock pile
    m_stock = new Card*[m_maxCards];
    ifNullCrash(m_stock);

    int i = 0;  // next available slot in m_stock[]

    for (int d = 0; d < decks; d++) {  // # of decks

        // iterate over suits
        for (unsigned int s = Card::Clubs; s <= Card::Spades; s++) {

            // iterate over point values
            for (unsigned int p = 2; p <= Card::Ace; p++) {

                if (p == 8) {
                    m_stock[i] = new Cruno8(s, p);
                } else {
                    m_stock[i] = new Card(s, p);  // insert new card
                }

                ifNullCrash(m_stock[i]);
                i++;
            }

            // TODO: Add the Skip and Reverse cards here.

            m_stock[i] = new CrunoDraw2(s, CrunoDraw2::DrawTwo);
            ifNullCrash(m_stock[i]);
            i++;
        }
    }

    // remember how many cards we added
    m_numStock = m_maxCards;

    // Still haven't started (need to have players added)
    m_started = false;
    m_over = false;
}
