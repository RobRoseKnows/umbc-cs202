/*
 * File:    CrunoGame.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * This is the CrunoGame class that adds neccessary logic and methods to
 * the Game class so that it can play a game of Cruno.
 */

// Macro to make an int index in the player array
// into a positive number because C++ mod is weird.
#include "CrunoGame.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "game.h"
#include "CrunoDraw2.h"
#include "Cruno8.h"
#include "CrunoSkip.h"
#include "CrunoReverse.h"

/**
 * Helper function from superclass.
 */
static void ifNullCrash(void *ptr) {
    if (ptr == NULL) {
        cerr << "Could not allocate memory\n";
        exit(1);
    }
    return;
}

CrunoGame::CrunoGame() {
    // Call super constructor to do most of the work.
    Game::Game();
    m_skipPlayerNumber = -1;
    m_directionConstant = 1;
}

/**
 * This method is used by CrunoDraw2 to get the pointer of a player by
 * their index in the player array.
 */
Player* CrunoGame::getPlayerPointer(int index) {
    return Game::m_players[index];
}

/**
 * Overrode initialize method to add the action cards to the deck and to
 * add Cruno8 cards as well.
 */
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
    m_maxCards = DECK_SIZE;

    if (numPlayers > 5) {
        // use two decks
        decks = 2;
        m_maxCards = 2 * DECK_SIZE;
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

            // Add two sets of cards each.
            for (int faceIndex = 0; faceIndex < 2; faceIndex++) {
                m_stock[i] = new CrunoDraw2(s, DrawTwo);
                ifNullCrash(m_stock[i]);
                i++;

                m_stock[i] = new CrunoSkip(s, Skip);
                ifNullCrash(m_stock[i]);
                i++;

                m_stock[i] = new CrunoReverse(s, Reverse);
                ifNullCrash(m_stock[i]);
                i++;
            }
        }
    }

    // remember how many cards we added
    m_numStock = m_maxCards;

    // Still haven't started (need to have players added)
    m_started = false;
    m_over = false;
}

/**
 * use % m_numPlayers to wrap around. Properly skips players as well.
 */
unsigned int CrunoGame::nextPlayer() {
    int nextPlayer = (m_currentPlayer + m_directionConstant) % m_numPlayers;

    // If player is supposed to be skipped, take the player after nextPlayer.
    if (nextPlayer == m_skipPlayerNumber) {
        nextPlayer = (nextPlayer + m_directionConstant) % m_numPlayers;
        // Since we have skipped the player, we now make sure he isn't
        // skipped again.
        m_skipPlayerNumber = -1;
    }

    // Set and return the current player
    m_currentPlayer = nextPlayer;
    return m_currentPlayer;
}

/**
 * This uses macros and mod to get the player that comes after
 * the current player. Does NOT take into consideration if the player
 * should be skipped. This is so it can be used to showCards to Players
 * in playGame().
 */
unsigned int CrunoGame::playerAfter(unsigned int thisPlayer) {
    // The positive macro here makes the next index positive.
    int nextPlayer = (thisPlayer + m_directionConstant) % m_numPlayers;
    return nextPlayer;
}

Card *CrunoGame::dealOneCard() {
   Card *cptr ;

   // Check to see if the stock is empty. If so, shuffle the discard into
   // stock.
   if (m_numStock < 1) {
       if(m_numDiscard < 1) {
           // Sanity check to make sure the players don't already have all the cards.
           m_over = true;
           return NULL;
       }
       shuffleCards();
   }

   // Gimme!
   //
   m_numStock-- ;
   cptr = m_stock[m_numStock] ;
   m_stock[m_numStock] = NULL ;

   return cptr ;
}

/**
 * This method shuffles all the cards in the discard pile into the stock
 * in order to keep the game going.
 */
void CrunoGame::shuffleCards() {
    bool shuffled = false;
    cout << "Discard is shuffled into the deck!" << endl;

    // Holds the last card that we keep in the discard array.
    Card* lastPlayed = m_discard[m_numDiscard - 1];

    for(unsigned int i = 0; i < m_numDiscard - 1; i++) {
        m_stock[i] = m_discard[i];
    }

    m_numStock = m_numDiscard - 1;
    m_numDiscard = 1;
    m_discard[0] = lastPlayed;

    int j;

    // This was taken from startGame to shuffle the deck.
    for(unsigned int i = 0 ; i < m_numStock ; i++) {
       Card *temp ;

       j = rand() % m_numStock ;
       temp = m_stock[i] ;
       m_stock[i] = m_stock[j] ;
       m_stock[j] = temp ;
    }
}

/**
 * This reverses the direction of play by negating the direction
 * constant.
 */
void CrunoGame::reversePlay() {

    cout << "Play is reversed!" << endl;
    m_directionConstant = -m_directionConstant;
}

/**
 * I chose to implement skipPlayer here rather than in CrunoSkip.cpp
 * because it was simpler and it would allow the nextPlayer() and
 * playerAfter() to properly display whether or not a player would be
 * skipped. It also means that nextPlayer() won't be called too many times.
 */
void CrunoGame::skipPlayer(int player) {
    cout << "Player " << player << " is skipped!" << endl;
    m_skipPlayerNumber = player;
}
